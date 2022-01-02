#include    "mm.h"

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