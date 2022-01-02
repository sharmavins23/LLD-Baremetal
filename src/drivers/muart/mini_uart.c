// Defines the functions for the mini UART.

#include "gpio.h"
#include "utils.h"
#include "peripherals/auxi.h"
#include "mini_uart.h"

// Pin definitions for UART serial functionality
#define TXD 14
#define RXD 15

// Initializes the UART serial port data transfer procedure
void uart_init() {
    // Set the functions for pins TXD, RXD
    gpio_pin_set_func(TXD, GFAlt5);
    gpio_pin_set_func(RXD, GFAlt5);

    // Enable the pins TXD, RXD
    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    // Enable Mini UART
    REGS_AUX->enables = 1;
    // Set Mini UART control to 0
    REGS_AUX->mu_control = 0;
    // Set active flags for Mini UART
    REGS_AUX->mu_ier = 0;
    // Set Mini UART to 8-bit mode
    REGS_AUX->mu_lcr = 3;
    REGS_AUX->mu_mcr = 0;

// Set the baud rate to 115,200 Hz (calculating from datasheet)
#if RPI_VERSION == 3
    REGS_AUX->mu_baud_rate = 270;  // = 115200 @ 250 Mhz
#endif

#if RPI_VERSION == 4
    REGS_AUX->mu_baud_rate = 541;  // = 115200 @ 500 Mhz
#endif

    // Set control to 3
    REGS_AUX->mu_control = 3;

    // Get debug output for Mini UART
    uart_send('\r');
    uart_send('\n');
    uart_send('\n');
}

// Receives a character
char uart_recv() {
    // Bit 1 is set if FIFO holds at least 1 byte
    while (!(REGS_AUX->mu_lsr & 1))
        ;

    // Once ready, receive the character through IO port
    return REGS_AUX->mu_io & 0xFF;  // Mask out upper bits
}

// Sends a character
void uart_send(char c) {
    // Bit 5 is set if FIFO can accept at least one byte
    while (!(REGS_AUX->mu_lsr & 0x20))  // 0x20 = 0010 0000 = Fifth bit
        ;

    // Once clear, send the character through IO port
    REGS_AUX->mu_io = c;
}

// Sends a string of characters
void uart_send_string(char *str) {
    // While the dereferenced value is not null...
    while (*str) {
        // If we send a line feed...
        if (*str == '\n') {
            // Send a carriage return as well
            uart_send('\r');
        }

        // Send the character
        uart_send(*str);
        // Iterate the pointer upwards
        str++;
    }
}