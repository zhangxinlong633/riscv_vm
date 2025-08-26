# RISC-V 指令集表格图片

本目录包含从 [RISC-V指令集速查表](https://five-embeddev.com/riscv-user-isa-manual/Priv-v1.12/instr-table.html) 下载的完整指令集表格。

## 图片说明

### instr-table_00.svg
**RV32I基础整数指令集 - 算术和逻辑指令**
- 算术指令：ADD, ADDI, SUB, LUI, AUIPC
- 比较指令：SLT, SLTI, SLTU, SLTIU
- 逻辑指令：AND, ANDI, OR, ORI, XOR, XORI

### instr-table_01.svg
**RV32I基础整数指令集 - 移位和分支指令**
- 移位指令：SLL, SLLI, SRL, SRLI, SRA, SRAI
- 分支指令：BEQ, BNE, BLT, BGE, BLTU, BGEU
- 跳转指令：JAL, JALR

### instr-table_02.svg
**RV32I基础整数指令集 - 加载/存储指令**
- 加载指令：LB, LH, LW, LBU, LHU
- 存储指令：SB, SH, SW
- 系统指令：FENCE, FENCE.I, ECALL, EBREAK

### instr-table_03.svg
**RV64I扩展指令集**
- 64位加载指令：LD, LWU
- 64位存储指令：SD
- 32位算术指令：ADDW, ADDIW, SUBW
- 32位移位指令：SLLW, SLLIW, SRLW, SRLIW, SRAW, SRAIW

### instr-table_04.svg
**M扩展 - 乘除法指令**
- 乘法指令：MUL, MULW
- 除法指令：DIV, DIVU, DIVW, DIVUW
- 取余指令：REM, REMU, REMW, REMUW

### instr-table_05.svg
**A扩展 - 原子内存操作指令**
- 加载保留/存储条件：LR.W, SC.W, LR.D, SC.D
- 原子内存操作：AMOADD.W, AMOSWAP.W, AMOXOR.W, AMOOR.W, AMOAND.W
- 原子比较操作：AMOMIN.W, AMOMAX.W, AMOMINU.W, AMOMAXU.W

### instr-table_06.svg
**Zicsr扩展 - 控制状态寄存器指令**
- CSR读写指令：CSRRW, CSRRS, CSRRC
- CSR立即数指令：CSRRWI, CSRRSI, CSRRCI
- 特权级指令：MRET, SRET, URET, WFI

## 使用说明

这些SVG格式的图片提供了完整的RISC-V指令集参考，包括：
- 指令格式和编码
- 操作码和功能码
- 寄存器字段
- 立即数字段
- 指令描述

图片来源于 [Five EmbedDev](https://five-embeddev.com/) 的RISC-V指令集手册，遵循CC BY 4.0许可协议。
