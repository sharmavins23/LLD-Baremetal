// Vectors defined in ARMv8 D13.2.137

// Initialize all defined interrupt vectors
.global     irq_init_vectors
irq_init_vectors:
            adr         x0, vectors         // Store the vector address
            msr         vbar_el1, x0        // Construct all vectors
            ret

// Vector enabling in ARMv8 C5.2.2
// Enable the IRQ
.global     irq_enable
irq_enable:
            msr         daifclr, #2
            ret

// Disable the IRQ
.global     irq_disable
irq_disable:
            msr         daifset, #2
            ret