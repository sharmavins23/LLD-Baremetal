#include "utils.h"
#include "printf.h"
#include "entry.h"
#include "peripherals/irq.h"
#include "peripherals/auxi.h"
#include "mini_uart.h"

// Series of print-friendly error messages in response to IRQs
const char entry_error_messages[16][32] = {
    // EL1t
    "SYNC_INVALID_EL1t",
    "IRQ_INVALID_EL1t",
    "FIQ_INVALID_EL1t",
    "ERROR_INVALID_EL1T",
    // EL1h
    "SYNC_INVALID_EL1h",
    "IRQ_INVALID_EL1h",
    "FIQ_INVALID_EL1h",
    "ERROR_INVALID_EL1h",
    // EL0, 64 bit
    "SYNC_INVALID_EL0_64",
    "IRQ_INVALID_EL0_64",
    "FIQ_INVALID_EL0_64",
    "ERROR_INVALID_EL0_64",
    // EL0, 32 bit
    "SYNC_INVALID_EL0_32",
    "IRQ_INVALID_EL0_32",
    "FIQ_INVALID_EL0_32",
    "ERROR_INVALID_EL0_32"};

// Show an invalid entry message upon an invalid entry through MUART
void show_invalid_entry_message(u32 type, u64 esr, u64 address) {
    printf("ERROR CAUGHT: %s - %d, ESR: %X, Address: %X\n",
           entry_error_messages[type],
           type,
           esr,
           address);
}

// Enable the interrupt controller to function
void enable_interrupt_controller() {
#if RPI_VERSION == 4
    REGS_IRQ->irq0_enable_0 = AUX_IRQ;
#endif

#if RPI_VERISON == 3
    REGS_IRQ->irq0_enable_1 = AUX_IRQ;
#endif
}

void handle_irq() {
    u32 irq;

#if RPI_VERSION == 4
    irq = REGS_IRQ->irq0_pending_0;
#endif

#if RPI_VERSION == 3
    irq = REGS_IRQ->irq0_pending_1;
#endif

    while (irq) {
        if (irq & AUX_IRQ) {
            irq &= ~AUX_IRQ;  // Loop and remove the bit we've handled

            // While there is data to be read... Read it
            while ((REGS_AUX->mu_iir & 4) == 4) {
                printf("UART Recv: ");
                uart_send(uart_recv());
                printf("\n");
            }
        }
    }
}