.global     _start
_start:
            ldr         w0, kernel_entry32  // Load the location of our kernel entry
            br          x0                  // Go to that

// Assembler directive - Ensure the data is within range of load instructions
.ltorg

// Firmware needs to find this exact value to verify the arm stub
.org        0xf0
.global     stub_magic
stub_magic:
            .word       0x5afe570b

// ARM stub versioning - Purely for show?
.org        0xf4
.global     stub_version
stub_version:
            .word       0

// 
.org        0xfc
.global     kernel_entry32
kernel_entry32:
            .word       0x0                 // Start from top of binary file