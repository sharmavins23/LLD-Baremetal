#include    "entry.h"

// When we enter the exception, we need to store all data
.macro      kernel_entry
            sub         sp, sp, #S_FRAME_SIZE // Make room on the stack pointer

                                            // Store all registers onto stack
            stp         x0, x1, [sp, #16 * 0]
            stp         x2, x3, [sp, #16 * 1]
            stp         x4, x5, [sp, #16 * 2]
            stp         x6, x7, [sp, #16 * 3]
            stp         x8, x9, [sp, #16 * 4]
            stp         x10, x11, [sp, #16 * 5]
            stp         x12, x13, [sp, #16 * 6]
            stp         x14, x15, [sp, #16 * 7]
            stp         x16, x17, [sp, #16 * 8]
            stp         x18, x19, [sp, #16 * 9]
            stp         x20, x21, [sp, #16 * 10]
            stp         x22, x23, [sp, #16 * 11]
            stp         x24, x25, [sp, #16 * 12]
            stp         x26, x27, [sp, #16 * 13]
            stp         x28, x29, [sp, #16 * 14]
            str         x30, [sp, #16 * 15] 
.endm

// When we leave the exception, we need to restore all data
.macro      kernel_exit
                                            // Restore all registers from stack
            ldp         x0, x1, [sp, #16 * 0]
            ldp         x2, x3, [sp, #16 * 1]
            ldp         x4, x5, [sp, #16 * 2]
            ldp         x6, x7, [sp, #16 * 3]
            ldp         x8, x9, [sp, #16 * 4]
            ldp         x10, x11, [sp, #16 * 5]
            ldp         x12, x13, [sp, #16 * 6]
            ldp         x14, x15, [sp, #16 * 7]
            ldp         x16, x17, [sp, #16 * 8]
            ldp         x18, x19, [sp, #16 * 9]
            ldp         x20, x21, [sp, #16 * 10]
            ldp         x22, x23, [sp, #16 * 11]
            ldp         x24, x25, [sp, #16 * 12]
            ldp         x26, x27, [sp, #16 * 13]
            ldp         x28, x29, [sp, #16 * 14]
            ldr         x30, [sp, #16 * 15]

            add         sp, sp, #S_FRAME_SIZE // Remove room from stack pointer

            eret                            // Return from the exception
.endm


// Macro to handle an invalid entry to the interrupt
.macro      handle_invalid_entry type
            kernel_entry
            mov         x0, #\type
            mrs         x1, esr_el1
            mrs         x2, elr_el1
            bl          show_invalid_entry_message
            b           err_hang
.endm

// Macro to align a specific label and jump to it
.macro      ventry      label
.align      7
            b           \label
.endm

// Exception vectors table
.align      11
.global     vectors
vectors:
            ventry        sync_invalid_el1t   // Synchronous EL1t
            ventry        irq_invalid_el1t    // IRQ EL1t
            ventry        fiq_invalid_el1t    // FIQ EL1t
            ventry        error_invalid_el1t  // Error EL1t

            ventry        sync_invalid_el1h   // Synchronous EL1h
            ventry        handle_el1_irq      // IRQ EL1h
            ventry        fiq_invalid_el1h    // FIQ EL1h
            ventry        error_invalid_el1h  // Error EL1h

            ventry        sync_invalid_el0_64    // Synchronous 64-bit EL0
            ventry        irq_invalid_el0_64  // IRQ 64-bit EL0
            ventry        fiq_invalid_el0_64  // FIQ 64-bit EL0
            ventry        error_invalid_el0_64// Error 64-bit EL0

            ventry        sync_invalid_el0_32    // Synchronous 32-bit EL0
            ventry        irq_invalid_el0_32  // IRQ 32-bit EL0
            ventry        fiq_invalid_el0_32  // FIQ 32-bit EL0
            ventry        error_invalid_el0_32// Error 32-bit EL0

// Synchronous EL1t
sync_invalid_el1t:
            handle_invalid_entry SYNC_INVALID_EL1t

// IRQ EL1t
irq_invalid_el1t:
            handle_invalid_entry IRQ_INVALID_EL1t

// FIQ EL1t
fiq_invalid_el1t:
            handle_invalid_entry FIQ_INVALID_EL1t

// Error EL1t
error_invalid_el1t:
            handle_invalid_entry ERROR_INVALID_EL1t

// Synchronous EL1h
sync_invalid_el1h:
            handle_invalid_entry SYNC_INVALID_EL1h

// IRQ EL1h
handle_el1_irq:
            kernel_entry                    // Store all registers on stack
            bl          handle_irq          // Handle the exception
            kernel_exit                     // Restore all registers from stack

// FIQ EL1h label
fiq_invalid_el1h:
            handle_invalid_entry FIQ_INVALID_EL1h

// Error EL1h
error_invalid_el1h:
            handle_invalid_entry ERROR_INVALID_EL1h

// Synchronous 64-bit EL0
sync_invalid_el0_64:
            handle_invalid_entry SYNC_INVALID_EL0_64

// IRQ 64-bit EL0
irq_invalid_el0_64:
            handle_invalid_entry IRQ_INVALID_EL0_64

// FIQ 64-bit EL0
fiq_invalid_el0_64:
            handle_invalid_entry FIQ_INVALID_EL0_64

// Error 64-bit EL0
error_invalid_el0_64:
            handle_invalid_entry ERROR_INVALID_EL0_64

// Synchronous 32-bit EL0
sync_invalid_el0_32:
            handle_invalid_entry SYNC_INVALID_EL0_32

// IRQ 32-bit EL0
irq_invalid_el0_32:
            handle_invalid_entry IRQ_INVALID_EL0_32

// FIQ 32-bit EL0
fiq_invalid_el0_32:
            handle_invalid_entry FIQ_INVALID_EL0_32

// Error 32-bit EL0
error_invalid_el0_32:
            handle_invalid_entry ERROR_INVALID_EL0_32

// In case of unknown error, hang the processor in the exception
.global     err_hang
err_hang:   
            b           err_hang