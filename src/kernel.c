#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"

// Printf initialization function for placing a simple character
void putc(void *p, char c) {
    if (c == '\n')
        putc(p, '\r');

    uart_send(c);
}

u32 get_el();

void kernel_main() {
    uart_init();

    // Initialize printf's formatting system with our putc function for UART
    init_printf(0, putc);

    printf("\nRaspberry Pi Bare Metal OS Initializing...\n");

    irq_init_vectors();
    enable_interrupt_controller();
    irq_enable();

#if RPI_VERSION == 3
    printf("\tRaspberry Pi 3 \n");
#elif RPI_VERSION == 4
    printf("\tRaspberry Pi 4 \n");
#endif

    printf("\nException level: %d\n", get_el());

    while (1) {
        // Hang the processor for now
        // uart_send(uart_recv());
    }
}