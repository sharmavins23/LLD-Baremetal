#pragma once
// Contains UART definitions for peripheral addressing.

#include "common.h"
#include "peripherals/base.h"

// Structure of the register mapping for auxiliary peripherals (UART only)
// RPI documentation 2.1 Overview
struct AuxRegs {
    reg32 irq_status;    // Auxiliary Interrupt Status
    reg32 enables;       // Auxiliary Enable
    reg32 reserved[14];  // (Padding, filler)
    reg32 mu_io;         // Mini UART I/O Data
    reg32 mu_ier;        // Mini UART Interrupt Enable
    reg32 mu_iir;        // Mini UART Interrupt Identify
    reg32 mu_lcr;        // Mini UART Line Control
    reg32 mu_mcr;        // Mini UART Modem Control
    reg32 mu_lsr;        // Mini UART Line Status
    reg32 mu_msr;        // Mini UART Modem Status
    reg32 mu_scratch;    // Mini UART Scratch
    reg32 mu_control;    // Mini UART Extra Control
    reg32 mu_status;     // Mini UART Extra Status
    reg32 mu_baud_rate;  // Mini UART Baud Rate
};

// Base offset of the auxiliary peripheral registers
#define REGS_AUX ((struct AuxRegs *)(PBASE + 0x00215000))