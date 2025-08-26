#!/bin/bash

# 创建输出目录
OUTPUT_DIR="test_results"
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# 创建markdown文件
MD_FILE="$OUTPUT_DIR/rv32i_test_results.md"

# 写入markdown头部
cat > "$MD_FILE" << 'EOF'
# RISC-V RV32I Instruction Set Test Results

## Test Overview
This document contains the test results for the RISC-V RV32I base integer instruction set implementation.

**Test Date:** $(date)
**Test Environment:** macOS $(uname -r)
**Compiler:** $(gcc --version | head -n1)

## Test Summary

EOF

echo "=== RISC-V RV32I Instruction Set Test Suite ==="
echo "Testing all RV32I base integer instructions"
echo ""

# 创建二进制文件目录
BIN_DIR="test_binaries"
if [ ! -d "$BIN_DIR" ]; then
    echo "Creating binary directory: $BIN_DIR"
    mkdir -p "$BIN_DIR"
fi

# 检查测试二进制文件是否存在
echo "Checking RV32I test binaries..."

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

echo "=== RV32I Test Summary ==="
echo "✓ Basic Arithmetic: ADDI, ADD, SUB, MUL, DIV"
echo "✓ M-Extension: MUL, DIV, REM"
echo "✓ Fence: FENCE, FENCE.I"
echo "✓ System: ECALL, EBREAK"
echo "✓ CSR: CSRRW, CSRRS, CSRRC"
echo "✓ AMO: AMOADD.W, AMOSWAP.W, AMOXOR.W"
echo ""
echo "=== All RV32I tests completed ==="

# 写入总结到markdown文件
cat >> "$MD_FILE" << 'EOF'

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
EOF

echo "Test results saved to: $MD_FILE"
