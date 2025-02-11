# Makefile (BSD style)

# 指定编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 源文件
SOURCES = riscv_vm.c cpu.c

# 目标文件
OBJECTS = riscv_vm.o cpu.o

# 可执行文件名
TARGET = riscv_vm

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

# 编译每个源文件为目标文件
riscv_vm.o: riscv_vm.c
	$(CC) $(CFLAGS) -c $< -o $@

cpu.o: cpu.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

