// Definitions for GPIO pin functions.

#include "gpio.h"
#include "utils.h"

// Sets a GPIO pin to a specified function
void gpio_pin_set_func(u8 pinNumber, GpioFunc func) {
    // Find start bit of the specific pin
    u8 bitStart = (pinNumber * 3) % 30;
    // Find the register corresponding to the pin
    u8 reg = pinNumber / 10;

    // Start with the selector from the GPIO Regs Struct
    u32 selector = REGS_GPIO->func_select[reg];
    selector &= ~(7 << bitStart);    // Clear the bits for the section
    selector |= (func << bitStart);  // Set the bits for the section

    // Write the new selector to the GPIO Regs Struct
    REGS_GPIO->func_select[reg] = selector;
}

// Enables a specific GPIO pin via clock registers
// Defined in Ch.6, GPIO Pull-up/down Clock Registers (GPPUDCLKn)
void gpio_pin_enable(u8 pinNumber) {
    // Write to GPPUD to set required control signal
    REGS_GPIO->pupd_enable = 0;

    // Wait 150 cycles
    delay(150);

    // Write to GPPUDCLK to set required control signal
    REGS_GPIO->pupd_enable_clocks[pinNumber / 32] = 1 << (pinNumber % 32);

    // Wait 150 cycles
    delay(150);

    // Write to GPPUD to remove control signal
    REGS_GPIO->pupd_enable = 0;

    // Write to GPPUDCLK to remove clock signal
    REGS_GPIO->pupd_enable_clocks[pinNumber / 32] = 0;
}

// Enables a GPIO pin for basic INPUT functionality
void gpio_pin_enable_input(u8 pinNumber) {
    gpio_pin_set_func(pinNumber, GFInput);
}

// Enables a GPIO pin for basic OUTPUT functionality
void gpio_pin_enable_output(u8 pinNumber) {
    gpio_pin_set_func(pinNumber, GFOutput);
}

// Outputs a HIGH value to a GPIO pin
void gpio_pin_set_high(u8 pinNumber) {
    REGS_GPIO->output_set.data[pinNumber / 32] = 1 << (pinNumber % 32);
}

// Outputs a LOW value to a GPIO pin
void gpio_pin_set_low(u8 pinNumber) {
    REGS_GPIO->output_clear.data[pinNumber / 32] = 1 << (pinNumber % 32);
}