# Makefile Explanation

The overarching goal of the Makefile is to simplify building within a
semi-dynamic filestructure.

## RPi Version and CPU structure

```makefile
RPI_VERSION ?= 4

ifeq ($(RPI_VERSION), 4)
CPU_VER = cortex-a72
else
CPU_VER = cortex-a53
endif

ifeq ($(RPI_VERSION), 4)
CPU_ARCH = bcm2711
else
CPU_ARCH = bcm2837
endif
```

The overarching project is governed by the RPI_VERSION parameter, flagged in the
makefile. This is a C operation that's passed in later.

The corresponding CPU structure portions are purely for verbosity.

| RPi Version | CPU Version | CPU Architecture |
| ----------- | ----------- | ---------------- |
| 4           | Cortex A72  | BCM 2711         |
| 3           | Cortex A53  | BCM 2837         |

## Directory structuring

```makefile
BOOTMNT = boot
BUILD_DIR = build
SRC_DIR = src
```

These specify the positions of various file directories within the project.
Source files are compiled from `SRC_DIR` into temporary build files in
`BUILD_DIR`. They are then loaded into `BOOTMNT` for deployment on the SD card.

The specification of these as variables is purely unnecessary.

## ARMGNU and AArch64 Cross Compilation

The `ARMGNU` variable contains the path executable for the cross compiler
toolchain's subtext. In this machine, it is specified as `aarch64-none-elf`.
Commands called are:

-   `aarch64-none-elf-gcc`: Compiling scripts from C and ASM code.
    -   This takes in `.c` and `.S` files and compiles them to `_c.o` and `_s.o`
        files.
-   `aarch64-none-elf-ld`: Linking scripts together via the linkerscript.
    -   This takes in all object files, and spits out a `kernel8.elf` file.
-   `aarch64-none-elf-objcopy`: Creating and copying a binary object file.
    -   This takes in `kernel8.elf` files and creates a binary `.img` file.

No other commands are called.

## C Operations and Flags

Despite having assembly code, the assembly code within repository is not
assembled; It is linked into C code and compiled via GCC.

| C Flag                | Meaning                                                                                                                                                  |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `-DRPI_VERSION`       | Passes in the Raspberry Pi version. `D` defines a macro to be used by the preprocessor; As such, `RPI_VERSION` is now a macro for all C code to utilize. |
| `-Wall`               | Enables all compiler warning messsages.                                                                                                                  |
| `-nostdlib`           | Tells GCC to not link in the `std` C libraries.                                                                                                          |
| `-nostartfiles`       | Forces `main()` to not be called at program entry.                                                                                                       |
| `-ffreestanding`      | Informs GCC that the standard library does not exist. Allows for overwriting of C `std` functions.                                                       |
| `-Iinclude`           | `-I` specifies the include folder path to be `include/`.                                                                                                 |
| `-mgeneral-regs-only` | Indicates that no floating-point or advanced SIMD registers should be used when generating code. Any explicit floating-point code will generate errors.  |
| `-mcpu`               | Details the CPU version. Not required.                                                                                                                   |
