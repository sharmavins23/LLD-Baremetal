#pragma once
// Simple utilty functions.

#include "common.h"

// Stalls the CPU pipeline for a certain number of ticks.
void delay(u64 ticks);
// Places 32'b of data into the specified memory address.
void put32(u64 address, u32 value);
// Gets 32'b of data from a specified memory address.
u32 get32(u64 address);
