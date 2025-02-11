#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
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

	int cpu_len = 0;

	if (argc != 2) {
		printf("usage: ./riscv_vm bin_file_name\n");
		exit(-1);
	}

	cpu_init(&cpu);

  	ret = util_read(bin_name, (char *)cpu.bus.dram.mem, 10240, &cpu_len);
	if (ret != 0) {
		goto exit;
	}

	while(TRUE) {
		uint32_t code = cpu_fetch(&cpu);

		cpu.pc += sizeof(uint32_t);

		ret = cpu_execute(&cpu, code);
		if (ret == 0) {
			break;
		}

		dump_registers(&cpu);

		if (cpu.pc == 0) {
			break;
		}
	}

exit:
	return ret;
}

