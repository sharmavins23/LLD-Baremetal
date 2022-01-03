# !!! Change this to your specific Raspberry Pi version
RPI_VERSION ?= 4

# Set the CPU versioning based on the Raspberry Pi version
ifeq ($(RPI_VERSION), 4)
CPU_VER = cortex-a72
else
CPU_VER = cortex-a53
endif

# Set the CPU architecture based on the Raspberry Pi version
ifeq ($(RPI_VERSION), 4)
CPU_ARCH = bcm2711
else
CPU_ARCH = bcm2837
endif

# Files to load to SD card (to deploy)
BOOTMNT = boot

# ARM cross compiler toolchain
ARMGNU ?= aarch64-none-elf

# C operations (to compile properly)
COPS = -DRPI_VERSION=$(RPI_VERSION) -Wall -nostdlib -nostartfiles -ffreestanding \
	   -Iinclude -mgeneral-regs-only -mcpu=$(CPU_VER)

# Directory for object files to live (and die)
BUILD_DIR = build

# Directory for OS source code to live
SRC_DIR = src

# File to make
all : kernel8.img

# Cleans up all object files and build directory
clean : 
	del $(BUILD_DIR)\*.img
	del $(BOOTMNT)\kernel8.img
	del $(BOOTMNT)\kernel8-rpi4.img

# Build targets for all C files
$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# Build targets for all assembly files
$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

# Build targets for all files (C and assembly, wildcards for all files in directory)
C_FILES = $(wildcard $(SRC_DIR)/*.c)
C_FILES += $(wildcard $(SRC_DIR)/*/*.c)
C_FILES += $(wildcard $(SRC_DIR)/*/*/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
ASM_FILES += $(wildcard $(SRC_DIR)/*/*.S)
ASM_FILES += $(wildcard $(SRC_DIR)/*/*/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

# Build targets for dependency files
DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

# Build target for kernel8.img
kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo Building for RPI $(value RPI_VERSION)
	@echo Deploy to $(value BOOTMNT)
	@echo Using $(value ARMGNU)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary $(BUILD_DIR)/kernel8.img
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary $(BOOTMNT)/kernel8-rpi4.img
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary $(BOOTMNT)/kernel8.img

armstub/build/armstub_s.o: armstub/src/armstub.S
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

armstub: armstub/build/armstub_s.o
	$(ARMGNU)-ld --section-start=.text=0 -o armstub/build/armstub.elf armstub/build/armstub_s.O
	$(ARMGNU)-objcopy armstub/build/armstub.elf -O binary armstub-new.bin
	$(ARMGNU)-objcopy armstub/build/armstub.elf -O binary $(BOOTMNT)/armstub-new.bin