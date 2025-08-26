# RISC-V 虚拟机模拟器

这是一个用C语言实现的RISC-V 64位虚拟机模拟器，支持RV32I和RV64I指令集，包含完整的测试套件。

## 功能特性

- **RISC-V 64位处理器模拟** (RV64I指令集，包含RV32I基础指令)
- **1MB DRAM内存系统**
- **完整的指令集支持**：
  - RV32I基础整数指令集
  - RV64I扩展指令集
  - M扩展（乘除法指令）
  - 32位算术指令（ADDIW, ADDW, SUBW等）
- **内存访问指令** (LW, SW, LD, SD等)
- **分支跳转指令** (BEQ, JAL, JALR等)
- **算术逻辑指令** (ADD, SUB, AND, OR等)
- **CSR寄存器支持**
- **压缩指令支持**
- **完整的测试套件**

## 快速开始

### 1. 构建项目

```bash
cd src
make
```

### 2. 运行测试

```bash
# 运行RV64I测试套件
cd test
./test_rv64i.sh

# 运行RV32I测试套件
./test_rv32i.sh
```

### 3. 运行单个测试程序

```bash
# 从src目录运行
cd src
./riscv_vm ../test/test_binaries/addi_test
./riscv_vm ../test/test_binaries/add_test
./riscv_vm ../test/test_binaries/sub_test
```

## 项目结构

```
riscv_vm/
├── src/
│   ├── riscv_vm.c     # 主程序入口
│   ├── cpu.c          # CPU核心实现
│   ├── cpu.h          # CPU头文件定义
│   ├── riscv_vm       # 编译后的可执行文件
│   └── Makefile       # 构建脚本
├── test/
│   ├── test_binaries/     # 测试二进制文件
│   │   ├── addi_test      # ADDI指令测试
│   │   ├── add_test       # ADD指令测试
│   │   ├── sub_test       # SUB指令测试
│   │   ├── mul_test       # MUL指令测试
│   │   ├── div_test       # DIV指令测试
│   │   ├── m_extension_test    # M扩展测试
│   │   ├── 32bit_arithmetic_test # 32位算术指令测试
│   │   ├── 32bit_shift_test     # 32位移位指令测试
│   │   ├── ld_sd_test           # 内存访问测试
│   │   ├── system_test          # 系统指令测试
│   │   └── ...                  # 更多测试程序
│   ├── test_results/        # 测试结果输出
│   │   ├── rv32i_test_results.md
│   │   └── rv64i_test_results.md
│   ├── spec/                # RISC-V规范文档
│   ├── test_rv32i.sh        # RV32I测试脚本
│   ├── test_rv64i.sh        # RV64I测试脚本
│   └── convert.py           # 测试工具脚本
└── README.md               # 项目说明文档
```

## 支持的指令集

### RV32I基础指令集
- **算术指令**: ADDI, ADD, SUB, SLT, SLTU
- **逻辑指令**: ANDI, AND, ORI, OR, XORI, XOR
- **移位指令**: SLLI, SLL, SRLI, SRL, SRAI, SRA
- **分支指令**: BEQ, BNE, BLT, BGE, BLTU, BGEU
- **跳转指令**: JAL, JALR
- **内存指令**: LB, LH, LW, LBU, LHU, SB, SH, SW
- **系统指令**: FENCE, ECALL, EBREAK

### RV64I扩展指令集
- **64位算术指令**: ADDIW, ADDW, SUBW, SLTIW, SLTUW
- **64位逻辑指令**: ANDIW, ORIW, XORIW
- **64位移位指令**: SLLIW, SLLW, SRLIW, SRLW, SRAIW, SRAW
- **64位内存指令**: LD, SD, LWU

### M扩展（乘除法）
- **乘法指令**: MUL, MULH, MULHSU, MULHU
- **除法指令**: DIV, DIVU, REM, REMU
- **64位乘除法**: MULW, DIVW, DIVUW, REMW, REMUW

## 内存映射

- **0x80000000 - 0x800FFFFF**: DRAM (1MB)
- 支持字节、半字、字、双字的内存访问

## 寄存器系统

- **32个通用寄存器** (x0-x31)
- **程序计数器** (PC)
- **CSR寄存器** (控制和状态寄存器)

## 测试套件

项目包含完整的测试套件，覆盖：

1. **基础算术测试**
   - ADDI, ADD, SUB指令
   - 32位和64位运算

2. **乘除法测试**
   - M扩展指令
   - 有符号和无符号运算

3. **内存访问测试**
   - 字节、半字、字、双字访问
   - 对齐和未对齐访问

4. **系统指令测试**
   - CSR操作
   - 特权级切换

5. **分支跳转测试**
   - 条件分支
   - 无条件跳转

## 构建要求

- GCC编译器
- Make工具
- RISC-V工具链（用于生成测试二进制文件）

## 使用示例

### 运行基础测试

```bash
# 进入src目录
cd src

# 运行ADDI测试
./riscv_vm ../test/test_binaries/addi_test

# 运行ADD测试
./riscv_vm ../test/test_binaries/add_test

# 运行SUB测试
./riscv_vm ../test/test_binaries/sub_test
```

### 运行完整测试套件

```bash
# 运行RV64I测试
cd test
./test_rv64i.sh

# 查看测试结果
cat test_results/rv64i_test_results.md
```

## 调试功能

模拟器提供详细的执行信息：

- **指令执行跟踪**: 显示每条指令的执行过程
- **寄存器状态**: 实时显示寄存器值变化
- **内存访问**: 显示内存读写操作
- **指令解码**: 显示指令的详细解码信息

## 清理

```bash
cd src
make clean
```

## 技术细节

### 指令执行流程

1. **取指**: 从内存中读取指令
2. **解码**: 解析指令格式和操作码
3. **执行**: 执行相应的操作
4. **写回**: 更新寄存器或内存

### 压缩指令支持

- 支持RISC-V压缩指令格式
- 自动检测16位和32位指令
- 正确的PC增量处理

### 异常处理

- 支持基本的异常检测
- 内存访问越界检查
- 非法指令检测

## 许可证

本项目采用MIT许可证。

## 贡献

欢迎提交Issue和Pull Request来改进这个项目！

## 相关资源

- [RISC-V官方规范](https://riscv.org/specifications/)
- [RISC-V指令集手册](https://github.com/riscv/riscv-isa-manual)
