#pragma once
// Contains declarations for read/write functions from UART serial ports.

// Initializes the UART serial port data transfer procedure.
void uart_init();
// Receives a character.
char uart_recv();
// Sends a character.
void uart_send(char c);
// Sends a string of characters.
void uart_send_string(char *str);
