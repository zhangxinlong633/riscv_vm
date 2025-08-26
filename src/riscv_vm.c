#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "cpu.h"

int util_read(char *path, char *buf, int buf_len, int *read_len)
{
	int ret = EINVAL;

	int fd = open(path, O_RDONLY);
	if (fd <= 0) {
		goto exit;
	}

	ret = read(fd, buf, buf_len);
	if (ret < 0) {
		ret = ENOMEM;
		goto exit;
	}
	*read_len = ret;

	ret = 0;

exit:
	if (fd > 0) {
		close(fd);
	}

	return ret;
}


int main(int argc, char **argv)
{
	int ret = EINVAL;
	char *bin_name = argv[1];
	struct CPU cpu = {0};

	int instruction_count = 0;

	if (argc != 2) {
		printf("Usage: ./riscv_vm <kernel_file>\n");
		printf("Example: ./riscv_vm ../test/addi\n");
		exit(-1);
	}

	printf("RISC-V Virtual Machine Starting...\n");
	printf("Loading binary file: %s\n", bin_name);

	cpu_init(&cpu);

	// 加载二进制文件
	int cpu_len = 0;
	ret = util_read(bin_name, (char *)cpu.bus.dram.mem, DRAM_SIZE, &cpu_len);
	if (ret != 0) {
		fprintf(stderr, "Error: Failed to read binary file %s\n", bin_name);
		goto exit;
	}
	printf("Loaded %d bytes into memory at 0x%x\n", cpu_len, (unsigned int)DRAM_BASE);

	printf("Starting execution...\n\n");

	while(TRUE) {
		uint32_t code = cpu_fetch(&cpu);
		
		if (code == 0) {
			printf("Reached end of program (null instruction)\n");
			break;
		}

		printf("Executing instruction %d at PC=0x%llx\n", instruction_count + 1, cpu.pc);
		
		// 检查是否是压缩指令
		if (code <= 0xFFFF && (code & 0x3) != 0x3) {
			cpu.pc += 2; // 压缩指令增加 2 字节
		} else {
			cpu.pc += 4; // 32 位指令增加 4 字节
		}

		ret = cpu_execute(&cpu, code);
		if (ret == 0) {
			printf("Execution stopped by instruction\n");
			break;
		}

		dump_registers(&cpu);
		instruction_count++;

		// 安全检查：防止无限循环
		if (instruction_count > 1000) {
			printf("Warning: Executed more than 1000 instructions, stopping\n");
			break;
		}

		if (cpu.pc == 0) {
			printf("PC reached 0, stopping execution\n");
			break;
		}
	}

	printf("\nExecution completed. Total instructions executed: %d\n", instruction_count);

exit:
	return ret;
}

