import time
import serial
import argparse
import zlib
import struct


CMD_START = 0x01
CMD_DATA  = 0X02
CMD_END   = 0x03
ACK  = 0x79
NACK = 0x1F

PACKET_SIZE = 256



def read_response(ser):
    val = ser.read(1)

    if len(val) != 1:
        raise RuntimeError("Timeout Waiting for the Bootloader")
    return val[0]


def send_Start(ser, firmware):
    size = len(firmware)
    crc  = zlib.crc32(firmware) & 0xFFFFFFFF
    print(f"Firmware size: {size}bytes")
    print(f"Frimware CRC: 0x{crc:08X}")

    packet = bytearray()

    packet.append(CMD_START)

    packet += struct.pack("<I", size)
    packet += struct.pack("<I", crc)

    ser.write(packet)

    response = read_response(ser)

    if response != ACK:
        raise RuntimeError(f"Bootloader rejected start" f"0x{response:02X}")


def send_data(ser, firmware):
    total = len(firmware)

    offset = 0

    while offset < total:
        chunk = firmware[offset : offset + PACKET_SIZE]
        crc = zlib.crc32(chunk) & 0xFFFFFFFF

        packet = bytearray()   #->which is used to carry the raw bytes

        packet.append(CMD_DATA)
        packet += struct.pack("<I", len(chunk))    # <-->liitle Endian I-->unsigned 4 byte  which all defined int the bootloader project
        packet += chunk
        packet += struct.pack("<I", crc)

        for attempt in range(5):
            ser.write(packet)

            response = read_response(ser)

            if response == ACK: break
            if response == NACK:
                print(f"Retry Packet at: {offset}")
                continue
        else:
            raise RuntimeError("Too Many retries")
        
        offset += len(chunk)
        percentage = (offset*100)//total
        print(f"\rProgress: {percentage:3d}%", end="", flush=True) # 3->minnimum d->decimal end->newline flush->live progression

    print()
    

def send_End(ser):
    ser.write(bytes([CMD_END]))    # Write excepts single byte so we conver the integer to the raw byte

    response = read_response(ser)

    if response != ACK:
        raise RuntimeError(f"Firmware Rejected " f"0x{response:02X}")   # 0->zero padding 2->minium 2 character X->uppercase



def main():

    parser = argparse.ArgumentParser()

    parser.add_argument("--port", required = True)
    parser.add_argument("--baud", type = int, default = 115200)
    parser.add_argument("--file", required=True)

    args = parser.parse_args()

    with open(args.file, "rb") as f:
        firmware = f.read()
    print("Connecting to the bootloader")

    with serial.Serial(args.port, args.baud, timeout=2) as ser:
        time.sleep(0.5)
        send_Start(ser, firmware)
        print("Sending Firmware.....")
        send_data(ser, firmware)
        print("Finishing update...")
        send_End(ser)
        print("Updated Successfully")


if __name__ == "__main__":
     main()