#############################################
# STM32F411RETx Makefile
#############################################

TARGET = Application

#############################################
# Toolchain
#############################################

PREFIX = arm-none-eabi

CC      = $(PREFIX)-gcc
AS      = $(PREFIX)-gcc
LD      = $(PREFIX)-gcc
OBJCOPY = $(PREFIX)-objcopy
SIZE    = $(PREFIX)-size

#############################################
# MCU
#############################################

CPU = cortex-m4

MCU_FLAGS = -mcpu=$(CPU) \
            -mthumb \
            -mfpu=fpv4-sp-d16 \
            -mfloat-abi=hard

#############################################
# Directories
#############################################

BUILD_DIR = build

DRIVER_INC = Drivers/Inc
DRIVER_SRC = Drivers/Src

APP_INC = Inc
APP_SRC = Src

STARTUP_DIR = Startup

#############################################
# Linker Script
#############################################

LDSCRIPT = STM32F411RETX_FLASH.ld

#############################################
# Include Paths
#############################################

C_INCLUDES = \
-I$(DRIVER_INC) \
-I$(APP_INC)

#############################################
# C Flags
#############################################

CFLAGS = $(MCU_FLAGS) \
         $(C_INCLUDES) \
         -DSTM32F411xE \
         -DUSE_FULL_LL_DRIVER \
         -Wall \
         -Wextra \
         -ffunction-sections \
         -fdata-sections \
         -g3 \
         -O0 \
         -std=gnu11

#############################################
# Assembly Flags
#############################################

ASFLAGS = $(MCU_FLAGS) \
          -g3 \
          -x assembler-with-cpp

#############################################
# Linker Flags
#############################################

LDFLAGS = $(MCU_FLAGS) \
          -T$(LDSCRIPT) \
          -Wl,--gc-sections \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
          --specs=nano.specs \
          --specs=nosys.specs

#############################################
# Source Files
#############################################

C_SOURCES = \
$(APP_SRC)/main.c \
$(APP_SRC)/syscalls.c \
$(APP_SRC)/sysmem.c \
$(DRIVER_SRC)/GPS_Driver.c \
$(DRIVER_SRC)/I2C_Driver.c \
$(DRIVER_SRC)/logdata.c \
$(DRIVER_SRC)/MPU6050_Driver.c \
$(DRIVER_SRC)/SPI_Driver.c \
$(DRIVER_SRC)/UART_Driver.c \
$(DRIVER_SRC)/W25j64_Driver.c

#############################################
# Startup File
#############################################

ASM_SOURCES = $(wildcard $(STARTUP_DIR)/*.s)

#############################################
# Object Files
#############################################

C_OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))

ASM_OBJECTS = $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

#############################################
# Default Target
#############################################

all: $(BUILD_DIR)/$(TARGET).elf \
     $(BUILD_DIR)/$(TARGET).bin \
     $(BUILD_DIR)/$(TARGET).hex

#############################################
# Create ELF
#############################################

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

#############################################
# C Compilation
#############################################

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#############################################
# Assembly Compilation
#############################################

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

#############################################
# Binary
#############################################

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

#############################################
# HEX
#############################################

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

#############################################
# Clean
#############################################

clean:
	rm -rf $(BUILD_DIR)

#############################################
# Flash
#############################################

flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f interface/stlink.cfg \
	        -f target/stm32f4x.cfg \
	        -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

#############################################
# Debug
#############################################

debug: $(BUILD_DIR)/$(TARGET).elf
	openocd -f interface/stlink.cfg \
	        -f target/stm32f4x.cfg

#############################################
# Information
#############################################

print:
	@echo "C sources:"
	@echo $(C_SOURCES)
	@echo ""
	@echo "Assembly:"
	@echo $(ASM_SOURCES)
	@echo ""
	@echo "Objects:"
	@echo $(OBJECTS)

.PHONY: all clean flash debug print
