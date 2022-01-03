#include    "mm.h"
#include    "sysregs.h"

.section    ".text.boot"

// Starts the processor up, verifying CPU ID and moving to master code.
.global     _start
_start:
            mrs         x0, mpidr_el1       // Pull CPUID out
            and         x0, x0, #0xFF       // Verify it's 0
            cbz         x0, master          // If it is, start up CPU
            b           proc_hang           // Otherwise, hang the processor

// Contains main memory initialization.
master:
                                            // Configure EL1 registers
            ldr         x0, =SCTLR_VALUE_MMU_DISABLED
            msr         sctlr_el1, x0       // Place the value into the special register

            ldr         x0, =HCR_VALUE      // Configure EL2 registers
            msr         hcr_el2, x0

            ldr         x0, =SCR_VALUE      // Configure EL3 registers
            msr         scr_el3, x0

            ldr         x0, =SPSR_VALUE     // Move to EL1 (specified in reg)
            msr         spsr_el3, x0

            adr         x0, el1_entry       // Once we're finished, jump to EL1
            msr         elr_el3, x0

            eret                            // Return from the exception level
                                            //  from EL3 to EL1

el1_entry:
            adr         x0, bss_begin
            adr         x1, bss_end
            sub         x1, x1, x0          // Clear out BSS section
            bl          memzero

            mov         sp, #LOW_MEMORY     // Set the stack pointer
            bl          kernel_main         // Branch to kernel main
            b           proc_hang           // Hang the processor

// Hangs the processor.
proc_hang:
            wfe
            b           proc_hang