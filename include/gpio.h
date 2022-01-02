#pragma once
// User headers for mini UART functionality and function selection

#include "peripherals/gpio.h"

typedef enum _GpioFunc {
    GFInput = 0,   // GPIO Pin is an input
    GFOutput = 1,  // GPIO Pin is an output
    GFAlt0 = 4,    // GPIO Pin takes alternate function 0
    GFAlt1 = 5,    // GPIO Pin takes alternate function 1
    GFAlt2 = 6,    // GPIO Pin takes alternate function 2
    GFAlt3 = 7,    // GPIO Pin takes alternate function 3
    GFAlt4 = 3,    // GPIO Pin takes alternate function 4
    GFAlt5 = 2     // GPIO Pin takes alternate function 5
} GpioFunc;

// GFAlt functions defined at https://www.dummies.com/article/technology/computers/hardware/raspberry-pi/raspberry-pi-gpio-pin-alternate-functions-143761

// Sets a GPIO pin to a specified function
void gpio_pin_set_func(u8 pinNumber, GpioFunc func);

// Enables a specific GPIO pin
void gpio_pin_enable(u8 pinNumber);

// Enables a GPIO pin for basic INPUT functionality
void gpio_pin_enable_input(u8 pinNumber);

// Enables a GPIO pin for basic OUTPUT functionality
void gpio_pin_enable_output(u8 pinNumber);

// Outputs a HIGH value to a GPIO pin
void gpio_pin_set_high(u8 pinNumber);

// Outputs a LOW value to a GPIO pin
void gpio_pin_set_low(u8 pinNumber);