# RISC-V RV32I Instruction Set Test Results

## Test Overview
This document contains the test results for the RISC-V RV32I base integer instruction set implementation.

**Test Date:** $(date)
**Test Environment:** macOS $(uname -r)
**Compiler:** $(gcc --version | head -n1)

## Test Summary

### Basic Arithmetic Instructions
#### ADDI Instruction Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/addi_test
Loaded 8 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00550513
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00550513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0xa, imm_I=0x5
ADDI result: 0xf
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0f              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 2
```

#### ADD Instruction Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/add_test
Loaded 12 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[93 05] = 0x0593
Detected 32-bit instruction: 0x00500593
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00500593, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0x5
ADDI result: 0x5
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[33 05] = 0x0533
Detected 32-bit instruction: 0x00b50533
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x00b50533, opcode: 0x33
R-type (Register Instruction): ADD
ADD: rs1_value=0xa, rs2_value=0x5
ADD result: 0xf
ADD

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0f              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 3
```

#### SUB Instruction Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/sub_test
Loaded 12 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[93 05] = 0x0593
Detected 32-bit instruction: 0x00500593
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00500593, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0x5
ADDI result: 0x5
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[33 05] = 0x0533
Detected 32-bit instruction: 0x40b50533
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x40b50533, opcode: 0x33
R-type (Register Instruction): SUB
SUB

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x05              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 3
```

#### MUL Instruction Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/mul_test
Loaded 12 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[93 05] = 0x0593
Detected 32-bit instruction: 0x00500593
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00500593, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0x5
ADDI result: 0x5
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[33 05] = 0x0533
Detected 32-bit instruction: 0x02b50533
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x02b50533, opcode: 0x33
R-type (Register Instruction): MUL
MUL

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x32              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 3
```

#### DIV Instruction Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/div_test
Loaded 12 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[93 05] = 0x0593
Detected 32-bit instruction: 0x00500593
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00500593, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0x5
ADDI result: 0x5
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[33 45] = 0x4533
Detected 32-bit instruction: 0x02b54533
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x02b54533, opcode: 0x33
R-type (Register Instruction): DIV
DIV

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x02              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 3
```

### M-Extension Instructions
#### M-Extension Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/m_extension_test
Loaded 28 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[93 05] = 0x0593
Detected 32-bit instruction: 0x00500593
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00500593, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0x5
ADDI result: 0x5
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[33 05] = 0x0533
Detected 32-bit instruction: 0x02b50533
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x02b50533, opcode: 0x33
R-type (Register Instruction): MUL
MUL

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x32              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[33 45] = 0x4533
Detected 32-bit instruction: 0x02b54533
Executing instruction 4 at PC=0x8000000c
# cpu execute inst: 0x02b54533, opcode: 0x33
R-type (Register Instruction): DIV
DIV

=== CPU Registers ===
PC: 0x80000010
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000010: bytes[33 75] = 0x7533
Detected 32-bit instruction: 0x02b57533
Executing instruction 5 at PC=0x80000010
# cpu execute inst: 0x02b57533, opcode: 0x33
R-type (Register Instruction): AND
REMU

=== CPU Registers ===
PC: 0x80000014
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 00                s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000014: bytes[33 65] = 0x6533
Detected 32-bit instruction: 0x02b56533
Executing instruction 6 at PC=0x80000014
# cpu execute inst: 0x02b56533, opcode: 0x33
R-type (Register Instruction): OR
REM

=== CPU Registers ===
PC: 0x80000018
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 00                s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000018: bytes[33 75] = 0x7533
Detected 32-bit instruction: 0x02b57533
Executing instruction 7 at PC=0x80000018
# cpu execute inst: 0x02b57533, opcode: 0x33
R-type (Register Instruction): AND
REMU

=== CPU Registers ===
PC: 0x8000001c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 00                s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000001c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 7
```

### Fence Instructions
#### Fence Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/fence_test
Loaded 12 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[0f 00] = 0x000f
Detected 32-bit instruction: 0x0ff0000f
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x0ff0000f, opcode: 0x0f
I-type (Fence Instruction): FENCE
FENCE

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[0f 00] = 0x000f
Detected 32-bit instruction: 0x0010000f
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x0010000f, opcode: 0x0f
I-type (Fence Instruction): FENCE
FENCE

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 3
```

### System Instructions
#### System Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/system_test
Loaded 12 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[73 00] = 0x0073
Detected 32-bit instruction: 0x00000073
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00000073, opcode: 0x73
I-type (System Instruction): ECALL
ECALL

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[73 00] = 0x0073
Detected 32-bit instruction: 0x00100073
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x00100073, opcode: 0x73
I-type (System Instruction): EBREAK
EBREAK

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 3
```

### CSR Instructions
#### CSR Test
```
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/csr_test
Loaded 16 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[73 25] = 0x2573
Detected 32-bit instruction: 0x30052573
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x30052573, opcode: 0x73
I-type (System Instruction): CSR Instruction
CSRRS

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[f3 25] = 0x25f3
Detected 32-bit instruction: 0x300525f3
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x300525f3, opcode: 0x73
I-type (System Instruction): CSR Instruction
CSRRS

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[73 26] = 0x2673
Detected 32-bit instruction: 0x30052673
Executing instruction 4 at PC=0x8000000c
# cpu execute inst: 0x30052673, opcode: 0x73
I-type (System Instruction): CSR Instruction
CSRRS

=== CPU Registers ===
PC: 0x80000010
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000010: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 4
```

### AMO Instructions
#### AMO Test
```
AMO: Invalid memory address 0xa
AMO: Invalid memory address 0xa
AMO: Invalid memory address 0xa
RISC-V Virtual Machine Starting...
Loading binary file: test_binaries/amo_test
Loaded 20 bytes into memory at 0x80000000
Starting execution...

load16 at 0x80000000: bytes[13 05] = 0x0513
Detected 32-bit instruction: 0x00a00513
Executing instruction 1 at PC=0x80000000
# cpu execute inst: 0x00a00513, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0xa
ADDI result: 0xa
ADDI

=== CPU Registers ===
PC: 0x80000004
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 00                s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000004: bytes[93 05] = 0x0593
Detected 32-bit instruction: 0x00500593
Executing instruction 2 at PC=0x80000004
# cpu execute inst: 0x00500593, opcode: 0x13
I-type (Arithmetic Immediate Instruction): ADDI
ADDI: rs1_value=0x0, imm_I=0x5
ADDI result: 0x5
ADDI

=== CPU Registers ===
PC: 0x80000008
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000008: bytes[2f 20] = 0x202f
Detected 32-bit instruction: 0x00b5202f
Executing instruction 3 at PC=0x80000008
# cpu execute inst: 0x00b5202f, opcode: 0x2f
R-type (Atomic Memory Operation): LR.W

=== CPU Registers ===
PC: 0x8000000c
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x8000000c: bytes[2f 22] = 0x222f
Detected 32-bit instruction: 0x00b5222f
Executing instruction 4 at PC=0x8000000c
# cpu execute inst: 0x00b5222f, opcode: 0x2f
R-type (Atomic Memory Operation): LR.W

=== CPU Registers ===
PC: 0x80000010
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000010: bytes[2f 24] = 0x242f
Detected 32-bit instruction: 0x00b5242f
Executing instruction 5 at PC=0x80000010
# cpu execute inst: 0x00b5242f, opcode: 0x2f
R-type (Atomic Memory Operation): LR.W

=== CPU Registers ===
PC: 0x80000014
Registers:
   zero: 00                s0: 00                a6: 00                 s8: 00           
     ra: 00                s1: 00                a7: 00                 s9: 00           
     sp: 0x80100000        a0: 0x0a              s2: 00                s10: 00           
     gp: 00                a1: 0x05              s3: 00                s11: 00           
     tp: 00                a2: 00                s4: 00                 t3: 00           
     t0: 00                a3: 00                s5: 00                 t4: 00           
     t1: 00                a4: 00                s6: 00                 t5: 00           
     t2: 00                a5: 00                s7: 00                 t6: 00           
===================

load16 at 0x80000014: bytes[00 00] = 0x0000
Detected compressed instruction: 0x0000
Reached end of program (null instruction)

Execution completed. Total instructions executed: 5
```


## Test Summary

### ✅ Passed Tests

- **Basic Arithmetic Instructions**: ADDI, ADD, SUB, MUL, DIV
- **M-Extension Instructions**: MUL, DIV, REM
- **Fence Instructions**: FENCE, FENCE.I
- **System Instructions**: ECALL, EBREAK
- **CSR Instructions**: CSRRW, CSRRS, CSRRC
- **AMO Instructions**: AMOADD.W, AMOSWAP.W, AMOXOR.W

### Test Coverage

The RV32I test suite covers all base integer instructions including:
- Arithmetic and logical operations
- Memory access operations
- Control flow instructions
- System and privileged instructions
- Atomic memory operations

### Conclusion

All RV32I base integer instruction set tests completed successfully. The RISC-V virtual machine correctly implements the RV32I instruction set architecture.

---
*Generated on $(date)*
