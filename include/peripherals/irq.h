#pragma once

#include "peripherals/base.h"
#include "common.h"

// Access interrupt from Mini UART
enum vc_irqs {  // VideoCore IRQs
    AUX_IRQ = (1 << 29)
};

// IRQ structure for RPi4
struct arm_irq_regs_2711 {
    reg32 irq0_pending_0;  // ARM Core 0 IRQ Enabled Interrupt Pending [31:0]
    reg32 irq0_pending_1;  // ARM Core 0 IRQ Enabled Interrupt Pending [63:32]
    reg32 irq0_pending_2;  // ARM Core 0 IRQ Enabled Interrupt Pending [79:64]
    reg32 res0;            // Padding
    reg32 irq0_enable_0;   // Write to Set ARM Core 0 IRQ Enable [31:0]
    reg32 irq0_enable_1;   // Write to Set ARM Core 0 IRQ Enable [63:32]
    reg32 irq0_enable_2;   // Write to Set ARM Core 0 IRQ Enable [79:64]
    reg32 res1;            // Padding
    reg32 irq0_disable_0;  // Write to Clear ARM Core 0 IRQ Enable [31:0]
    reg32 irq0_disable_1;  // Write to Clear ARM Core 0 IRQ Enable [63:32]
    reg32 irq0_disable_2;  // Write to Clear ARM Core 0 IRQ Enable [79:64]
};

// IRQ structure for RPi3
struct arm_irq_regs_2837 {
    reg32 irq0_pending_0;  // ARM Core 0 IRQ Enabled Interrupt Pending [31:0]
    reg32 irq0_pending_1;  // ARM Core 0 IRQ Enabled Interrupt Pending [63:32]
    reg32 irq0_pending_2;  // ARM Core 0 IRQ Enabled Interrupt Pending [79:64]
    reg32 fiq_control;     // ARM Core 0 Fast IRQ Control
    reg32 irq0_enable_1;   // Write to Set ARM Core 0 IRQ Enable [63:32]
    reg32 irq0_enable_2;   // Write to Set ARM Core 0 IRQ Enable [79:64]
    reg32 irq0_enable_0;   // Write to Set ARM Core 0 IRQ Enable [31:0]
    reg32 res;             // Padding
    reg32 irq0_disable_1;  // Write to Clear ARM Core 0 IRQ Enable [63:32]
    reg32 irq0_disable_2;  // Write to Clear ARM Core 0 IRQ Enable [79:64]
    reg32 irq0_disable_0;  // Write to Clear ARM Core 0 IRQ Enable [31:0]
};

// Set the IRQ structure for the specific RPi version
#if RPI_VERSION == 3
typedef struct arm_irq_regs_2837 arm_irq_regs;
#endif
#if RPI_VERSION == 4
typedef struct arm_irq_regs_2711 arm_irq_regs;
#endif

#define REGS_IRQ ((arm_irq_regs *)(PBASE + 0x0000B200))