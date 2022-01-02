// Simple utilty functions.

// Stalls the CPU pipeline for a certain number of ticks.
// x0 (u64) ticks       Tick count for CPU stall
.global     delay
delay:
            subs        x0, x0, #1          // Subtract one tick from x0 count
            bne         delay               // If not zero, repeat
            ret

// Places 32'b of data into the specified memory address.
// x0 (u64) address     Address to place data in
// w1 (u32) value       Value to place
.global     put32
put32:
            str         w1, [x0]            // Store value w1 in address x0
            ret

// Gets 32'b of data from a specified memory address.
// x0 (u64) address     Address to receive data from
// w0 (u32) value       Value return
.global     get32
get32:
            ldr         w0, [x0]            // Load value w0 from address x0
            ret
