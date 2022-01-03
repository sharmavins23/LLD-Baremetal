# Exception Levels

## Overview

The exception levels fall under four categories, and the number order increases
with increasing privilege. They are:

| Level | Context     |
| ----- | ----------- |
| EL0   | Application |
| EL1   | Rich OS     |
| EL2   | Hypervisor  |
| EL3   | Firmware    |

Exception levels can only be switched via an exception call or exception return.

Each exception level is a different level of privileges to various functions of
the processor. The Raspberry Pi firmware boots into EL3, and the bootstub
generally initializes some sequences before passing to the hypervisor. The
hypervisor level passes control to the OS kernel.

Typically, the OS kernel runs in EL1, and any applications that it executes run
in EL0.

## Legacy

On legacy machines, older Raspberry Pi OS models were capable of booting
straight into EL3. However, if we log the exception level blankly, we note that
we are running in the context of EL2.

In the newer Raspberry Pi code, we note that there's a new tool called
`armstub.` This contains some code to switch to EL2. In order to do this, we
generate our own `armstub` section that is capable of passing straight into EL3
without spinning extra cores or other brute-force work.
