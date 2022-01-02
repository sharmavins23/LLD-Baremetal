#pragma once
// Contains declarations for memory management/stack management functions.

// Definitions for pages, page tables from linux src
#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

// Lowest memory address (start of stack)
#define LOW_MEMORY (2 * SECTION_SIZE)

// Assembler breaks if function definitions in C-style are included
#ifndef __ASSEMBLER__

// Stores N null bits(?) starting in a specified address.
void memzero(unsigned long src, unsigned int n);

#endif