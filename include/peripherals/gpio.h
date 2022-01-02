#pragma once
// Contains GPIO definitions for register addressing

#include "common.h"
#include "peripherals/base.h"

// Structure of a single pin's triple-mapping
struct GpioPinData {
    reg32 reserved;  // (Padding, filler)
    reg32 data[2];   // Pin data SET0, SET1
};

// Structure of the register mapping for GPIO
// RPI documentation 6.1 Register View
struct GpioRegs {
    reg32 func_select[6];                 // GPIO Function Selects
    struct GpioPinData output_set;        // GPIO Output Set
    struct GpioPinData output_clear;      // GPIO Output Clear
    struct GpioPinData level;             // GPIO Pin Level
    struct GpioPinData ev_detect_status;  // GPIO Event Detect Status
    struct GpioPinData re_detect_enable;  // GPIO Rising Edge Detect Enable
    struct GpioPinData fe_detect_enable;  // GPIO Falling Edge Detect Enable
    struct GpioPinData hi_detect_enable;  // GPIO High Detect Enable
    struct GpioPinData lo_detect_enable;  // GPIO Low Detect Enable
    struct GpioPinData async_re_detect;   // GPIO Asynchronous Rising Edge Detect
    struct GpioPinData async_fe_detect;   // GPIO Asynchronous Falling Edge Detect
    reg32 reserved;                       // (Padding, filler)
    reg32 pupd_enable;                    // GPIO Pull-up/Pull-down Enable
    reg32 pupd_enable_clocks[2];          // GPIO Pull-up/Pull-down Enable Clocks
};

// Base offset of the GPIO registers
#define REGS_GPIO ((struct GpioRegs *)(PBASE + 0x00200000))