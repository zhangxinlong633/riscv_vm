# RISC-V Virtual Machine Makefile
# 用于构建 RISC-V 64位虚拟机

# 目标文件
RISCV_VM = riscv_vm

# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
LDFLAGS = -lm

# 默认目标
all: $(RISCV_VM)

# 构建主虚拟机
$(RISCV_VM): riscv_vm.c cpu.c
	@echo "构建 RISC-V 虚拟机..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "构建完成: $@"

# 运行测试
test: $(RISCV_VM)
	@echo "运行 RISC-V 指令集测试..."
	@cd ../test && ./test_rv32i.sh && ./test_rv64i.sh

# 清理构建文件
clean:
	@echo "清理构建文件..."
	rm -f $(RISCV_VM)
	rm -f *.o
	@echo "清理完成"

# 显示帮助
help:
	@echo "=== RISC-V Virtual Machine Makefile 帮助 ==="
	@echo ""
	@echo "可用目标:"
	@echo "  all   - 构建 RISC-V 虚拟机 (默认)"
	@echo "  test  - 运行指令集测试"
	@echo "  clean - 清理构建文件"
	@echo "  help  - 显示此帮助"
	@echo ""
	@echo "使用示例:"
	@echo "  make      - 构建虚拟机"
	@echo "  make test - 运行测试"
	@echo "  make clean- 清理构建文件"

.PHONY: all test clean help
