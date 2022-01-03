#pragma once

// Initialize all defined interrupt vectors
void irq_init_vectors();
// Enable the IRQ
void irq_enable();
// Disable the IRQ
void irq_disable();

// Enable the interrupt controller to function
void enable_interrupt_controller();