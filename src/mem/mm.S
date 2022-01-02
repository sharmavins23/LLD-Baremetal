// Contains declarations for memory management/stack management functions.

// Stores N null bits(?) starting in a specified address.
// x0 (u64) src         Address to clear at
// x1 (u32) n           Number of bytes to clear
.global     memzero
memzero:
            str         xzr, [x0], #8       // Zero a byte in memory
            subs        x1, x1, #8          // Subtract from our counter
            b.gt        memzero             // Branch until byte count is 0
            ret