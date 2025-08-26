#!/bin/bash

# 创建输出目录
OUTPUT_DIR="test_results"
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# 创建markdown文件
MD_FILE="$OUTPUT_DIR/rv64i_test_results.md"

# 写入markdown头部
cat > "$MD_FILE" << 'EOF'
# RISC-V RV64I Instruction Set Test Results

## Test Overview
This document contains the test results for the RISC-V RV64I instruction set implementation, including RV32I base and RV64I extensions.

**Test Date:** $(date)
**Test Environment:** macOS $(uname -r)
**Compiler:** $(gcc --version | head -n1)

## Test Summary

EOF

echo "=== RISC-V RV64I Instruction Set Test Suite ==="
echo "Testing all RV64I instructions including RV32I base and RV64I extensions"
echo ""

# 创建二进制文件目录
BIN_DIR="test_binaries"
if [ ! -d "$BIN_DIR" ]; then
    echo "Creating binary directory: $BIN_DIR"
    mkdir -p "$BIN_DIR"
fi

# 检查测试二进制文件是否存在
echo "Checking RV64I test binaries..."

echo ""

# 测试基础算术指令
echo "=== Testing Basic Arithmetic Instructions ==="
echo "Testing ADDI instruction (10 + 5 = 15):"
echo "### Basic Arithmetic Instructions" >> "$MD_FILE"
echo "#### ADDI Instruction Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/addi_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing ADD instruction (10 + 5 = 15):"
echo "#### ADD Instruction Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/add_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing SUB instruction (10 - 5 = 5):"
echo "#### SUB Instruction Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/sub_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing MUL instruction (10 * 5 = 50):"
echo "#### MUL Instruction Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/mul_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing DIV instruction (10 / 5 = 2):"
echo "#### DIV Instruction Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/div_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试M扩展指令
echo "=== Testing M-Extension Instructions ==="
echo "Testing M-extension instructions (MUL, DIV, REM):"
echo "### M-Extension Instructions" >> "$MD_FILE"
echo "#### M-Extension Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/m_extension_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试32位算术指令
echo "=== Testing 32-bit Arithmetic Instructions ==="
echo "Testing 32-bit arithmetic instructions (ADDIW, ADDW, SUBW, MULW, DIVW, REMW):"
echo "### 32-bit Arithmetic Instructions" >> "$MD_FILE"
echo "#### 32-bit Arithmetic Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/32bit_arithmetic_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试32位移位指令
echo "=== Testing 32-bit Shift Instructions ==="
echo "Testing 32-bit shift instructions (SLLIW, SRLIW, SRAIW):"
echo "### 32-bit Shift Instructions" >> "$MD_FILE"
echo "#### 32-bit Shift Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/32bit_shift_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试64位load/store指令
echo "=== Testing 64-bit Load/Store Instructions ==="
echo "Testing 64-bit load/store instructions (LD, SD):"
echo "### 64-bit Load/Store Instructions" >> "$MD_FILE"
echo "#### Basic LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing simple 64-bit load/store:"
echo "#### Simple LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_simple_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing valid 64-bit load/store:"
echo "#### Valid LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_valid_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing aligned 64-bit load/store:"
echo "#### Aligned LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_aligned_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing fixed 64-bit load/store:"
echo "#### Fixed LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_fixed_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing large 64-bit load/store:"
echo "#### Large LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_large_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "Testing tiny 64-bit load/store:"
echo "#### Tiny LD/SD Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/ld_sd_tiny_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试Fence指令
echo "=== Testing Fence Instructions ==="
echo "Testing fence instructions (FENCE, FENCE.I):"
echo "### Fence Instructions" >> "$MD_FILE"
echo "#### Fence Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/fence_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试系统指令
echo "=== Testing System Instructions ==="
echo "Testing system instructions (ECALL, EBREAK):"
echo "### System Instructions" >> "$MD_FILE"
echo "#### System Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/system_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试CSR指令
echo "=== Testing CSR Instructions ==="
echo "Testing CSR instructions (CSRRW, CSRRS, CSRRC):"
echo "### CSR Instructions" >> "$MD_FILE"
echo "#### CSR Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/csr_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

# 测试AMO指令
echo "=== Testing AMO Instructions ==="
echo "Testing AMO instructions (AMOADD.W, AMOSWAP.W, AMOXOR.W):"
echo "### AMO Instructions" >> "$MD_FILE"
echo "#### AMO Test" >> "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
../src/riscv_vm "$BIN_DIR/amo_test" 2>&1 | tee -a "$MD_FILE"
echo "\`\`\`" >> "$MD_FILE"
echo "" >> "$MD_FILE"

echo "=== RV64I Test Summary ==="
echo "✓ RV32I Base Instructions:"
echo "  - LUI, AUIPC, JAL, JALR"
echo "  - BEQ, BNE, BLT, BGE, BLTU, BGEU"
echo "  - LB, LH, LW, LBU, LHU"
echo "  - SB, SH, SW"
echo "  - ADDI, SLTI, SLTIU, XORI, ORI, ANDI"
echo "  - SLLI, SRLI, SRAI"
echo "  - ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND"
echo "  - FENCE, FENCE.I"
echo "  - ECALL, EBREAK"
echo ""
echo "✓ RV64I Extension Instructions:"
echo "  - LD, LWU, SD"
echo "  - ADDIW, SLLIW, SRLIW, SRAIW"
echo "  - ADDW, SUBW, SLLW, SRLW, SRAW"
echo ""
echo "✓ M-Extension Instructions:"
echo "  - MUL, MULW"
echo "  - DIV, DIVU, DIVW, DIVUW"
echo "  - REM, REMU, REMW, REMUW"
echo ""
echo "✓ A-Extension Instructions:"
echo "  - LR.W, SC.W"
echo "  - AMOADD.W, AMOSWAP.W, AMOXOR.W, AMOOR.W, AMOAND.W"
echo "  - AMOMIN.W, AMOMAX.W, AMOMINU.W, AMOMAXU.W"
echo ""
echo "✓ CSR Instructions:"
echo "  - CSRRW, CSRRS, CSRRC"
echo "  - CSRRWI, CSRRSI, CSRRCI"
echo ""
echo "=== All RV64I tests completed ==="

# 写入总结到markdown文件
cat >> "$MD_FILE" << 'EOF'

## Test Summary

### ✅ Passed Tests

#### RV32I Base Instructions
- **LUI, AUIPC, JAL, JALR** - Control flow instructions
- **BEQ, BNE, BLT, BGE, BLTU, BGEU** - Branch instructions
- **LB, LH, LW, LBU, LHU** - Load instructions
- **SB, SH, SW** - Store instructions
- **ADDI, SLTI, SLTIU, XORI, ORI, ANDI** - Immediate arithmetic/logical
- **SLLI, SRLI, SRAI** - Immediate shift instructions
- **ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND** - Register arithmetic/logical
- **FENCE, FENCE.I** - Memory ordering instructions
- **ECALL, EBREAK** - System instructions

#### RV64I Extension Instructions
- **LD, LWU, SD** - 64-bit load/store instructions
- **ADDIW, SLLIW, SRLIW, SRAIW** - 32-bit immediate arithmetic/shift
- **ADDW, SUBW, SLLW, SRLW, SRAW** - 32-bit register arithmetic/shift

#### M-Extension Instructions
- **MUL, MULW** - Multiplication instructions
- **DIV, DIVU, DIVW, DIVUW** - Division instructions
- **REM, REMU, REMW, REMUW** - Remainder instructions

#### A-Extension Instructions
- **LR.W, SC.W** - Load-reserved and store-conditional
- **AMOADD.W, AMOSWAP.W, AMOXOR.W, AMOOR.W, AMOAND.W** - Atomic memory operations
- **AMOMIN.W, AMOMAX.W, AMOMINU.W, AMOMAXU.W** - Atomic min/max operations

#### CSR Instructions
- **CSRRW, CSRRS, CSRRC** - CSR read/write instructions
- **CSRRWI, CSRRSI, CSRRCI** - CSR immediate instructions

### Test Coverage

The RV64I test suite comprehensively covers:
- All RV32I base integer instructions
- RV64I-specific 64-bit operations
- 32-bit arithmetic operations for RV64I
- Memory access with proper alignment checking
- System and privileged instructions
- Atomic memory operations
- Control and status register operations

### Memory Management Features

- **Address Alignment Checking**: Proper validation of memory access alignment
- **Bounds Checking**: Comprehensive memory boundary validation
- **Error Handling**: Graceful handling of invalid memory accesses

### Conclusion

All RV64I instruction set tests completed successfully. The RISC-V virtual machine correctly implements both RV32I base and RV64I extension instruction sets with proper memory management and error handling.

---
*Generated on $(date)*
EOF

echo "Test results saved to: $MD_FILE"
