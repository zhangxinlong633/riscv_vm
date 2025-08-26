# xv6-emu: RISC-V 64位硬件模拟器

这是一个用C语言实现的RISC-V 64位硬件模拟器，专门用于运行xv6-riscv64操作系统。

## 功能特性

- **RISC-V 64位处理器模拟** (RV64I指令集)
- **1MB DRAM内存系统**
- **UART串口设备** (支持终端输入输出)
- **CLINT核心本地中断器**
- **PLIC平台级中断控制器**
- **ELF文件加载器**
- **交互式调试界面**

## 快速开始

### 1. 构建项目

```bash
# 构建所有程序
make all

# 或者只构建模拟器
make src/xv6-emu
```

### 2. 运行xv6操作系统

```bash
# 方法1: 使用Makefile
make run

# 方法2: 使用运行脚本（推荐）
./run.sh
```

这将会：
1. 自动构建xv6-riscv内核（如果还没有构建）
2. 启动模拟器
3. 加载并运行xv6操作系统
4. 进入xv6的shell环境

**推荐使用 `./run.sh`**，它提供了更友好的用户界面，类似于xv6-riscv的`make qemu`命令。

### 3. 其他运行选项

```bash
# 运行调试模式（显示详细指令执行信息）
make debug

# 运行演示程序（简化版本）
make demo

# 只构建xv6内核
make kernel
```

## 交互命令

在模拟器运行时，您可以输入以下命令：

- `h` - 显示帮助信息
- `r` - 显示寄存器状态
- `m` - 显示内存内容
- `s` - 单步执行
- `q` - 退出模拟器

## 项目结构

```
riscv_vm/
├── src/
│   ├── xv6_emu.c      # 主模拟器代码
│   ├── cpu.c          # CPU实现
│   ├── elf_loader.c   # ELF文件加载器
│   └── simple_demo.c  # 演示程序
├── test/
│   └── real_project/
│       └── xv6-riscv/ # xv6操作系统源码
├── Makefile           # 构建脚本
└── README.md          # 本文件
```

## 构建要求

- GCC编译器
- Make工具
- RISC-V工具链（用于构建xv6内核）

## 使用示例

### 运行完整的xv6操作系统

```bash
# 推荐方式
./run.sh

# 或者使用Makefile
make run
```

启动后，您将看到xv6操作系统的启动信息，然后进入shell环境：

```
xv6 kernel is booting

hart 2 starting
hart 1 starting
init: starting sh
$ 
```

在xv6 shell中，您可以运行各种命令：

```bash
$ ls
$ cat README
$ echo hello
$ grep xv6 README
```

### 运行演示程序

```bash
make demo
```

演示程序会展示模拟器的基本功能，包括：
- CPU状态显示
- 内存内容查看
- 单步执行
- 寄存器状态

## 调试功能

模拟器提供了丰富的调试功能：

1. **寄存器查看**: 实时查看所有RISC-V寄存器的值
2. **内存查看**: 查看指定地址的内存内容
3. **单步执行**: 逐条指令执行，便于调试
4. **指令解码**: 显示当前执行的指令信息

## 清理

```bash
# 清理构建文件
make clean

# 完全清理（包括xv6内核）
make distclean
```

## 帮助

```bash
# 显示Makefile帮助
make help
```

## 技术细节

### 支持的指令集

- RV64I基础整数指令集
- 内存访问指令 (LW, SW, LD, SD等)
- 分支跳转指令 (BEQ, JAL, JALR等)
- 算术逻辑指令 (ADD, SUB, AND, OR等)

### 内存映射

- 0x80000000 - 0x800FFFFF: DRAM (1MB)
- 0x10000000 - 0x1000FFFF: UART
- 0x2000000 - 0x200BFFF: CLINT
- 0x0C000000 - 0x0C200000: PLIC

### 中断处理

- 支持软件中断和定时器中断
- CLINT处理核心本地中断
- PLIC处理外部设备中断

## 许可证

本项目采用MIT许可证。

## 贡献

欢迎提交Issue和Pull Request来改进这个项目！
