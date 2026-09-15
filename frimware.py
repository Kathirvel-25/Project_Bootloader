import argparse
import struct 
import time
import zlib

import serial

CMD_START = 0x01
CMD_DATA = 0x02
CMD_END = 0x03

ACK = 0x79
NACK = 0x1F

PACKET_SIZE = 256


def read_response(ser, timeout = None):
    old_timeout = ser.timeout

    if timeout is not None:
        ser.timeout = timeout
    
    value = ser.read(1)

    ser.timeout = old_timeout

    if len(value) != 1:
        raise RuntimeError("Timeout waiting for bootloader")

    return value[0]
    

def send_start(ser, frimware):

    size = len(frimware)
    crc = zlib.crc32(frimware) & 0xFFFFFFFF
    print(f"Frimware size: {size}bytes")
    print(f"Frimware crc: 0x{crc:08X}")

    packet = bytearray()
    packet.append(CMD_START)

    packet += struct.pack("<I", size)
    packet += struct.pack("<I", crc)

    ser.write(packet)

    response = read_response(ser, timeout = 10)

    if response != ACK:
        raise RuntimeError(
            f"Bootloader rejected start: "
            f"0x{response:02X}"
        )

def send_data(ser, firmware):
    total = len(firmware)

    offset = 0

    while offset < total:

        chunk = firmware[
            offset:
            offset + PACKET_SIZE
        ]

        crc = zlib.crc32(chunk) & 0xFFFFFFFF

        packet = bytearray()

        packet.append(CMD_DATA)

        packet += struct.pack(
            "<I",
            len(chunk)
        )

        packet += chunk

        packet += struct.pack(
            "<I",
            crc
        )

        for attempt in range(5):

            ser.write(packet)

            response = read_response(ser)

            if response == ACK:
                break

            if response == NACK:
                print(
                    f"Retry packet at "
                    f"{offset}"
                )
                continue

            raise RuntimeError(
                f"Unexpected response: "
                f"0x{response:02X}"
            )

        else:
            raise RuntimeError(
                "Too many retries"
            )

        offset += len(chunk)

        percent = (offset * 100) // total

        print(
            f"\rProgress: "
            f"{percent:3d}%",
            end="",
            flush=True
        )

    print()


def send_end(ser):
    ser.write(
        bytes([CMD_END])
    )

    response = read_response(ser)

    if response != ACK:
        raise RuntimeError(
            f"Firmware rejected: "
            f"0x{response:02X}"  
        ) 


def main():

    parser = argparse.ArgumentParser()

    parser.add_argument( "--port", required=True)
    parser.add_argument( "--baud", type=int, default=115200)
    parser.add_argument( "--file", required=True)

    args = parser.parse_args()

    with open(args.file, "rb") as f:
        frimware = f.read()
    print("Connecting to the Bootloader")

    with serial.Serial(args.port, args.baud, timeout = 10) as ser:
        time.sleep(0.5)
        send_start(ser, frimware)
        print("Sending Frimware")
        send_data(ser, frimware)
        print("Finishing Update....")
        send_end(ser)
        print("Frimware update succfull...")


if __name__ == "__main__":
     main()