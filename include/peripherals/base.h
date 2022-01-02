#pragma once

// https://github.com/raspberrypi/linux/blob/rpi-5.10.y/arch/arm/boot/dts/bcm2837.dtsi
// soc -> ranges Peripheral address listed as 0x3F000000
#if RPI_VERSION == 3
#define PBASE 0x3F000000

// https://github.com/raspberrypi/linux/blob/rpi-5.10.y/arch/arm/boot/dts/bcm2711.dtsi
// soc -> ranges Peripheral address listed as 0xFE000000
#elif RPI_VERSION == 4
#define PBASE 0xFE000000

#else
#define PBASE 0
#error RPI_VERSION NOT DEFINED

#endif