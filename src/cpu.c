#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cpu.h"

/* https://five-embeddev.com/riscv-user-isa-manual/Priv-v1.12/instr-table.html */

#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[31m"
#define ANSI_RESET   "\x1b[0m"

#define ADDR_MISALIGNED(addr) (addr & 0x3)
#define ADDR_MISALIGNED_8(addr) (addr & 0x7)

#include <stdio.h>
#include <stdint.h>

// 掩码和位移常量
#define OPCODE_MASK 0x7F
#define FUNCT3_MASK 0x7000
#define FUNCT7_MASK 0xFE000000
#define RS1_MASK    0xF8000
#define RS2_MASK    0x1F00000
#define RD_MASK     0xF80

// 提取字段的宏
#define GET_OPCODE(inst) ((inst) & OPCODE_MASK)
#define GET_FUNCT3(inst) (((inst) & FUNCT3_MASK) >> 12)
#define GET_FUNCT7(inst) (((inst) & FUNCT7_MASK) >> 25)

// 定义操作码常量
enum OPCODES {
	OPCODE_LOAD    = 0x03,
	OPCODE_STORE   = 0x23,
	OPCODE_BRANCH  = 0x63,
	OPCODE_OP_IMM  = 0x13,
	OPCODE_OP      = 0x33,
	OPCODE_SYSTEM  = 0x73,
	OPCODE_FENCE   = 0x0F,
	OPCODE_OP_IMM_32 = 0x1B,
	OPCODE_OP_32   = 0x3B,
	OPCODE_AMO     = 0x2F
};

// 打印指令类型和具体指令的函数
void dump_instruction(uint32_t inst) 
{
	uint32_t opcode = GET_OPCODE(inst);
	uint32_t funct3 = GET_FUNCT3(inst);
	uint32_t funct7 = GET_FUNCT7(inst);

	switch (opcode) {
		case OPCODE_LOAD:
			printf("I-type (Load Instruction): ");
			switch (funct3) {
				case 0x0: printf("LB\n"); break;
				case 0x1: printf("LH\n"); break;
				case 0x2: printf("LW\n"); break;
				case 0x3: printf("LD\n"); break;
				case 0x4: printf("LBU\n"); break;
				case 0x5: printf("LHU\n"); break;
				case 0x6: printf("LWU\n"); break;
				default: printf("Unknown Load Instruction\n"); break;
			}
			break;
		case OPCODE_STORE:
			printf("S-type (Store Instruction): ");
			switch (funct3) {
				case 0x0: printf("SB\n"); break;
				case 0x1: printf("SH\n"); break;
				case 0x2: printf("SW\n"); break;
				case 0x3: printf("SD\n"); break;
				default: printf("Unknown Store Instruction\n"); break;
			}
			break;
		case OPCODE_BRANCH:
			printf("B-type (Branch Instruction): ");
			switch (funct3) {
				case 0x0: printf("BEQ\n"); break;
				case 0x1: printf("BNE\n"); break;
				case 0x4: printf("BLT\n"); break;
				case 0x5: printf("BGE\n"); break;
				case 0x6: printf("BLTU\n"); break;
				case 0x7: printf("BGEU\n"); break;
				default: printf("Unknown Branch Instruction\n"); break;
			}
			break;
		case JAL:
			printf("J-type (JAL Instruction)\n");
			break;
		case JALR:
			printf("I-type (JALR Instruction)\n");
			break;
		case LUI:
			printf("U-type (LUI Instruction)\n");
			break;
		case AUIPC:
			printf("U-type (AUIPC Instruction)\n");
			break;
		case OPCODE_OP_IMM:
			printf("I-type (Arithmetic Immediate Instruction): ");
			switch (funct3) {
				case 0x0: printf("ADDI\n"); break;
				case 0x2: printf("SLTI\n"); break;
				case 0x3: printf("SLTIU\n"); break;
				case 0x4: printf("XORI\n"); break;
				case 0x6: printf("ORI\n"); break;
				case 0x7: printf("ANDI\n"); break;
				case 0x1: printf("SLLI\n"); break;
				case 0x5:
						  if (funct7 == 0x00) {
							  printf("SRLI\n");
						  } else if (funct7 == 0x20) {
							  printf("SRAI\n");
						  } else {
							  printf("Unknown Shift Immediate Instruction\n");
						  }
						  break;
				default: printf("Unknown Immediate Instruction\n"); break;
			}
			break;
		case OPCODE_OP:
			printf("R-type (Register Instruction): ");
			switch (funct3) {
				case 0x0:
					if (funct7 == 0x00) {
						printf("ADD\n");
					} else if (funct7 == 0x20) {
						printf("SUB\n");
					} else if (funct7 == 0x01) {
						printf("MUL\n");
					} else {
						printf("Unknown ADD/SUB/MUL Instruction\n");
					}
					break;
				case 0x1: printf("SLL\n"); break;
				case 0x2: printf("SLT\n"); break;
				case 0x3: printf("SLTU\n"); break;
				case 0x4: 
					if (funct7 == 0x01) {
						printf("DIV\n");
					} else {
						printf("XOR\n");
					}
					break;
				case 0x5:
						  if (funct7 == 0x00) {
							  printf("SRL\n");
						  } else if (funct7 == 0x20) {
							  printf("SRA\n");
						  } else if (funct7 == 0x01) {
							  printf("DIVU\n");
						  } else {
							  printf("Unknown Shift Instruction\n");
						  }
						  break;
				case 0x6: printf("OR\n"); break;
				case 0x7: printf("AND\n"); break;
				default: printf("Unknown Register Instruction\n"); break;
			}
			break;
		case OPCODE_OP_IMM_32:
			printf("I-type (32-bit Arithmetic Immediate Instruction): ");
			switch (funct3) {
				case 0x0: printf("ADDIW\n"); break;
				case 0x1: printf("SLLIW\n"); break;
				case 0x5:
					if (funct7 == 0x00) {
						printf("SRLIW\n");
					} else if (funct7 == 0x20) {
						printf("SRAIW\n");
					} else {
						printf("Unknown 32-bit Shift Immediate Instruction\n");
					}
					break;
				default: printf("Unknown 32-bit Immediate Instruction\n"); break;
			}
			break;
		case OPCODE_OP_32:
			printf("R-type (32-bit Register Instruction): ");
			switch (funct3) {
				case 0x0:
					if (funct7 == 0x00) {
						printf("ADDW\n");
					} else if (funct7 == 0x20) {
						printf("SUBW\n");
					} else if (funct7 == 0x01) {
						printf("MULW\n");
					} else {
						printf("Unknown 32-bit ADD/SUB/MUL Instruction\n");
					}
					break;
				case 0x1: printf("SLLW\n"); break;
				case 0x4: 
					if (funct7 == 0x01) {
						printf("DIVW\n");
					} else {
						printf("Unknown 32-bit Instruction\n");
					}
					break;
				case 0x5:
					if (funct7 == 0x00) {
						printf("SRLW\n");
					} else if (funct7 == 0x20) {
						printf("SRAW\n");
					} else if (funct7 == 0x01) {
						printf("DIVUW\n");
					} else {
						printf("Unknown 32-bit Shift Instruction\n");
					}
					break;
				case 0x6: 
					if (funct7 == 0x01) {
						printf("REMW\n");
					} else {
						printf("Unknown 32-bit Instruction\n");
					}
					break;
				case 0x7: 
					if (funct7 == 0x01) {
						printf("REMUW\n");
					} else {
						printf("Unknown 32-bit Instruction\n");
					}
					break;
				default: printf("Unknown 32-bit Register Instruction\n"); break;
			}
			break;
		case OPCODE_FENCE:
			printf("I-type (Fence Instruction): ");
			if (funct3 == 0x0) {
				printf("FENCE\n");
			} else if (funct3 == 0x1) {
				printf("FENCE.I\n");
			} else {
				printf("Unknown Fence Instruction\n");
			}
			break;
		case OPCODE_SYSTEM:
			printf("I-type (System Instruction): ");
			if (funct3 == 0x0) {
				if ((inst >> 20) == 0x0) {
					printf("ECALL\n");
				} else if ((inst >> 20) == 0x1) {
					printf("EBREAK\n");
				} else {
					printf("Unknown System Instruction\n");
				}
			} else {
				printf("CSR Instruction\n");
			}
			break;
		case OPCODE_AMO:
			printf("R-type (Atomic Memory Operation): ");
			switch (funct3) {
				case 0x2: printf("LR.W\n"); break;
				case 0x3: printf("SC.W\n"); break;
				case 0x1: printf("AMOSWAP.W\n"); break;
				case 0x0: printf("AMOADD.W\n"); break;
				case 0x4: printf("AMOXOR.W\n"); break;
				case 0x8: printf("AMOOR.W\n"); break;
				case 0xC: printf("AMOAND.W\n"); break;
				case 0x10: printf("AMOMIN.W\n"); break;
				case 0x14: printf("AMOMAX.W\n"); break;
				case 0x18: printf("AMOMINU.W\n"); break;
				case 0x1C: printf("AMOMAXU.W\n"); break;
				default: printf("Unknown AMO Instruction\n"); break;
			}
			break;
		default:
			printf("Unknown Instruction\n");
			break;
	}
}


uint64_t load8(DRAM* dram, uint64_t addr) 
{
	return (uint64_t) dram->mem[addr - DRAM_BASE];
}

uint64_t load16(DRAM* dram, uint64_t addr) 
{
	uint64_t result = (uint64_t) dram->mem[addr - DRAM_BASE]
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 1] << 8);
	
	// 调试：打印读取的字节
	printf("load16 at 0x%llx: bytes[%02x %02x] = 0x%04x\n", 
	       addr, 
	       dram->mem[addr - DRAM_BASE],
	       dram->mem[addr - DRAM_BASE + 1],
	       (uint16_t)result);
	
	return result;
}

uint64_t load32(DRAM* dram, uint64_t addr) 
{
	uint64_t result = (uint64_t) dram->mem[addr - DRAM_BASE]
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 1] << 8)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 2] << 16)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 3] << 24);
	
	// 调试：打印读取的字节（已注释）
	
	return result;
}

uint64_t load64(DRAM* dram, uint64_t addr) 
{
	// Check bounds
	if (addr < DRAM_BASE || addr + 7 >= DRAM_BASE + DRAM_SIZE) {
		fprintf(stderr, "load64: Address out of bounds 0x%llx (DRAM: 0x%llx-0x%llx)\n", addr, DRAM_BASE, DRAM_BASE + DRAM_SIZE - 1);
		return 0;
	}
	
	return (uint64_t) dram->mem[addr - DRAM_BASE]
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 1] << 8)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 2] << 16)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 3] << 24)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 4] << 32)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 5] << 40)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 6] << 48)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 7] << 56);
}

uint64_t load(DRAM* dram, uint64_t addr, uint64_t size) 
{
	switch (size) {
		case 8:  return load8(dram, addr);
		case 16: return load16(dram, addr);
		case 32: return load32(dram, addr);
		case 64: return load64(dram, addr);
		default: return 0; // handle invalid size
	}
}

void store8(DRAM* dram, uint64_t addr, uint64_t value) 
{
	// Check bounds
	if (addr < DRAM_BASE || addr >= DRAM_BASE + DRAM_SIZE) {
		fprintf(stderr, "store8: Address out of bounds 0x%llx\n", addr);
		return;
	}
	
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
}

void store16(DRAM* dram, uint64_t addr, uint64_t value) 
{
	// Check bounds
	if (addr < DRAM_BASE || addr + 1 >= DRAM_BASE + DRAM_SIZE) {
		fprintf(stderr, "store16: Address out of bounds 0x%llx\n", addr);
		return;
	}
	
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
	dram->mem[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
}

void store32(DRAM* dram, uint64_t addr, uint64_t value) 
{
	// Check bounds
	if (addr < DRAM_BASE || addr + 3 >= DRAM_BASE + DRAM_SIZE) {
		fprintf(stderr, "store32: Address out of bounds 0x%llx\n", addr);
		return;
	}
	
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
	dram->mem[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
	dram->mem[addr - DRAM_BASE + 2] = (uint8_t) ((value >> 16) & 0xff);
	dram->mem[addr - DRAM_BASE + 3] = (uint8_t) ((value >> 24) & 0xff);
}

void store64(DRAM* dram, uint64_t addr, uint64_t value) 
{
	// Check bounds - addr + 7 must be within range
	if (addr < DRAM_BASE || addr + 7 >= DRAM_BASE + DRAM_SIZE) {
		fprintf(stderr, "store64: Address out of bounds 0x%llx (DRAM: 0x%llx-0x%llx)\n", addr, DRAM_BASE, DRAM_BASE + DRAM_SIZE - 1);
		return;
	}
	
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
	dram->mem[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
	dram->mem[addr - DRAM_BASE + 2] = (uint8_t) ((value >> 16) & 0xff);
	dram->mem[addr - DRAM_BASE + 3] = (uint8_t) ((value >> 24) & 0xff);
	dram->mem[addr - DRAM_BASE + 4] = (uint8_t) ((value >> 32) & 0xff);
	dram->mem[addr - DRAM_BASE + 5] = (uint8_t) ((value >> 40) & 0xff);
	dram->mem[addr - DRAM_BASE + 6] = (uint8_t) ((value >> 48) & 0xff);
	dram->mem[addr - DRAM_BASE + 7] = (uint8_t) ((value >> 56) & 0xff);
}

void store(DRAM* dram, uint64_t addr, uint64_t size, uint64_t value) 
{
	switch (size) {
		case 8:  store8(dram, addr, value); break;
		case 16: store16(dram, addr, value); break;
		case 32: store32(dram, addr, value); break;
		case 64: store64(dram, addr, value); break;
		default: ; // handle invalid size
	}
}

// Print operation for DEBUG
void print_op(const char* s) 
{
	printf("%s%s%s", ANSI_BLUE, s, ANSI_RESET);
}

// 添加调试信息输出函数
void debug_print(const char* format, ...) 
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    printf("[DEBUG] ");
    vprintf(format, args);
    va_end(args);
#endif
}

// 内存转储函数，用于调试
void dump_memory(DRAM* dram, uint64_t addr, uint64_t size) 
{
#ifdef DEBUG
    printf("Memory dump at 0x%llx (size: %llu bytes):\n", addr, size);
    for (uint64_t i = 0; i < size && i < 64; i += 4) {
        uint32_t value = load32(dram, addr + i);
        printf("  0x%llx: 0x%08x\n", addr + i, value);
    }
    if (size > 64) {
        printf("  ... (truncated)\n");
    }
#endif
}

void cpu_init(CPU *cpu) 
{
	// 初始化所有寄存器为0
	for (int i = 0; i < 32; i++) {
		cpu->regs[i] = 0x00;
	}
	
	// 初始化CSR寄存器
	for (int i = 0; i < 4096; i++) {
		cpu->csr[i] = 0x00;
	}
	
	// 设置一些基本的CSR值
	cpu->csr[MHARTID] = 0;  // 硬件线程ID
	cpu->csr[MVENDORID] = 0; // 厂商ID
	cpu->csr[MARCHID] = 0;   // 架构ID
	cpu->csr[MIMPID] = 0;    // 实现ID
	
	cpu->regs[0] = 0x00; // Register x0 hardwired to 0
	cpu->regs[2] = DRAM_BASE + DRAM_SIZE; // Set stack pointer
	cpu->pc = DRAM_BASE; // Set program counter to the base address
	
	    // printf("CPU initialized: PC=0x%llx, SP=0x%llx\n", cpu->pc, cpu->regs[2]);
}

uint32_t cpu_fetch(CPU *cpu) 
{
	// 首先尝试读取 16 位指令
	uint16_t inst16 = bus_load(&(cpu->bus), cpu->pc, 16);
	
	// 检查是否是压缩指令 (最低两位不为 11)
	if ((inst16 & 0x3) != 0x3) {
		// 这是压缩指令，返回 16 位指令
		printf("Detected compressed instruction: 0x%04x\n", inst16);
		return (uint32_t)inst16;
	} else {
		// 这是 32 位指令，读取完整的 32 位
		uint32_t inst32 = bus_load(&(cpu->bus), cpu->pc, 32);
		printf("Detected 32-bit instruction: 0x%08x\n", inst32);
		return inst32;
	}
}

uint64_t load_cpu(CPU* cpu, uint64_t addr, uint64_t size) 
{
	return bus_load(&(cpu->bus), addr, size);
}

void store_cpu(CPU* cpu, uint64_t addr, uint64_t size, uint64_t value) 
{
	bus_store(&(cpu->bus), addr, size, value);
}

// Instruction Decoder Functions
uint64_t get_rd(uint32_t inst) 
{
	return (inst >> 7) & 0x1f; // rd in bits 11..7
}

uint64_t get_rs1(uint32_t inst) 
{
	return (inst >> 15) & 0x1f; // rs1 in bits 19..15
}

uint64_t get_rs2(uint32_t inst) 
{
	return (inst >> 20) & 0x1f; // rs2 in bits 24..20
}

void dump_registers(CPU *cpu) 
{
	const char* abi[] = {
		"zero", "ra",  "sp",  "gp",
		"tp", "t0",  "t1",  "t2",
		"s0", "s1",  "a0",  "a1",
		"a2", "a3",  "a4",  "a5",
		"a6", "a7",  "s2",  "s3",
		"s4", "s5",  "s6",  "s7",
		"s8", "s9", "s10", "s11",
		"t3", "t4",  "t5",  "t6",
	};

	printf("\n=== CPU Registers ===\n");
	printf("PC: 0x%llx\n", cpu->pc);
	printf("Registers:\n");
	
	for (int i = 0; i < 8; i++) {
		printf("   %4s: %#-13.2llx  ", abi[i], cpu->regs[i]);
		printf("   %2s: %#-13.2llx  ", abi[i + 8], cpu->regs[i + 8]);
		printf("   %2s: %#-13.2llx  ", abi[i + 16], cpu->regs[i + 16]);
		printf("   %3s: %#-13.2llx\n", abi[i + 24], cpu->regs[i + 24]);
	}
	printf("===================\n\n");
}

uint64_t csr_read(CPU* cpu, uint64_t csr) 
{
	return (uint64_t)(uint32_t)cpu->csr[csr];
}

void csr_write(CPU* cpu, uint64_t csr, uint64_t value) 
{
	cpu->csr[csr] = value;
}

uint64_t bus_load(BUS* bus, uint64_t addr, uint64_t size) 
{
	return load(&(bus->dram), addr, size);
}

void bus_store(BUS* bus, uint64_t addr, uint64_t size, uint64_t value) 
{
	store(&(bus->dram), addr, size, value);
}

void set_reg_value_rd(CPU *cpu, uint32_t inst, uint32_t value)
{
	cpu->regs[get_rd(inst)] = value;
}

uint32_t get_reg_value_rs1(CPU *cpu, uint32_t inst)
{
	return cpu->regs[get_rs1(inst)];
}

uint32_t get_reg_value_rs2(CPU *cpu, uint32_t inst)
{

	return cpu->regs[get_rs2(inst)];
}


uint64_t get_imm_I(uint32_t inst) {
	return ((int64_t)(int32_t)(inst & 0xfff00000)) >> 20; // Signed immediate
}
uint64_t get_imm_S(uint32_t inst) {
	return ((int64_t)(int32_t)(inst & 0xfe000000) >> 20)
		| ((inst >> 7) & 0x1f);
}
uint64_t get_imm_B(uint32_t inst) {
	return ((int64_t)(int32_t)(inst & 0x80000000) >> 19)
		| ((inst & 0x80) << 4) // imm[11]
		| ((inst >> 20) & 0x7e0) // imm[10:5]
		| ((inst >> 7) & 0x1e); // imm[4:1]
}

uint64_t get_imm_U(uint32_t inst) 
{
	return (int64_t)(int32_t)(inst & 0xfffff000); // Upper immediate
}

uint64_t get_imm_J(uint32_t inst) 
{
	return (uint64_t)((int64_t)(int32_t)(inst & 0x80000000) >> 11)
		| (inst & 0xff000) // imm[19:12]
		| ((inst >> 9) & 0x800) // imm[11]
		| ((inst >> 20) & 0x7fe); // imm[10:1]
}

uint32_t get_shamt(uint32_t inst) 
{
	return (uint32_t)(get_imm_I(inst) & 0x1f); // Shift amount
}

uint64_t get_csr(uint32_t inst) 
{
	return ((inst & 0xfff00000) >> 20); // CSR
}

void exec_LUI(CPU* cpu, uint32_t inst) 
{
	cpu->regs[get_rd(inst)] = (uint64_t)(int64_t)(int32_t)(inst & 0xfffff000);
	print_op("lui\n");
}

void exec_AUIPC(CPU* cpu, uint32_t inst) 
{
	uint64_t imm = get_imm_U(inst);
	cpu->regs[get_rd(inst)] = ((int64_t) cpu->pc + (int64_t) imm) - 4;
	print_op("auipc\n");
}

void exec_JAL(CPU* cpu, uint32_t inst) 
{
	uint64_t imm = get_imm_J(inst);
	cpu->regs[get_rd(inst)] = cpu->pc;
	cpu->pc = cpu->pc + (int64_t) imm - 4;
	print_op("jal\n");
	if (ADDR_MISALIGNED(cpu->pc)) {
		fprintf(stderr, "JAL pc address misaligned");
		exit(0);
	}
}

void exec_JALR(CPU* cpu, uint32_t inst) 
{
    uint64_t imm = get_imm_I(inst);
    uint64_t tmp = cpu->pc;
    cpu->pc = (get_reg_value_rs1(cpu, inst) + (int64_t) imm) & ~1;
    cpu->regs[get_rd(inst)] = tmp;
    /*print_op("NEXT -> %#lx, imm:%#lx\n", cpu->pc, imm);*/
    print_op("jalr\n");
    if (ADDR_MISALIGNED(cpu->pc)) {
        fprintf(stderr, "JALR pc address misaligned");
        exit(0);
    }
}

// CSR instructions
void exec_CSR(CPU* cpu, uint32_t inst, uint32_t funct3, uint32_t imm_I) 
{
	switch (funct3) {
		case ECALLBREAK:    
			if (imm_I == 0x0) {
				printf("ECALL\n");
				// ECALL - Environment call
				// In a real implementation, this would trigger a system call
				// For now, we'll just print and continue
			} else if (imm_I == 0x1) {
				printf("EBREAK\n");
				// EBREAK - Environment break
				// In a real implementation, this would trigger a debugger break
				// For now, we'll just print and continue
			}
			break;
		case CSRRW  :  
    		cpu->regs[get_rd(inst)] = csr_read(cpu, get_csr(inst));
    		csr_write(cpu, get_csr(inst), cpu->regs[get_rs1(inst)]);
			printf("CSRRW\n");
			break;
		case CSRRS  :  
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] | cpu->regs[get_rs1(inst)]);
			printf("CSRRS\n");
			break;
		case CSRRC  :  
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] & ~(cpu->regs[get_rs1(inst)]) );
			printf("CSRRC\n");
			break;
		case CSRRWI :  
    		csr_write(cpu, get_csr(inst), get_rs1(inst));
			printf("CSRRWI\n");
			break;
		case CSRRSI :  
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] | get_rs1(inst));
			printf("CSRRSI\n");
			break;
		case CSRRCI :   
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] & ~get_rs1(inst));
			printf("CSRRCI\n");
			break; 
		default:
			return ;
	}
}

// FENCE instruction
void exec_FENCE(CPU *cpu, uint32_t inst, uint32_t funct3)
{
	switch (funct3) {
		case 0x0: // FENCE
			printf("FENCE\n");
			// FENCE - Memory fence
			// In a real implementation, this would ensure memory ordering
			// For now, we'll just print and continue
			break;
		case 0x1: // FENCE.I
			printf("FENCE.I\n");
			// FENCE.I - Instruction fence
			// In a real implementation, this would flush the instruction cache
			// For now, we'll just print and continue
			break;
		default:
			fprintf(stderr, "Unknown fence instruction: funct3=0x%x\n", funct3);
			break;
	}
}

// AMO_W
void exec_AMO_W(CPU *cpu, uint32_t inst, uint32_t funct3, uint32_t funct7, uint32_t rs1_value, uint32_t rs2_value)
{
	// Check if address is within valid memory range
	if (rs1_value < DRAM_BASE || rs1_value >= DRAM_BASE + DRAM_SIZE) {
		fprintf(stderr, "AMO: Invalid memory address 0x%x\n", rs1_value);
		return;
	}
	
	uint32_t tmp = load_cpu(cpu, rs1_value, 32);
	uint32_t res = 0;
	
	switch (funct7 >> 2) { 
		case LR_W: 
			printf("LR.W\n");
			cpu->regs[get_rd(inst)] = tmp;
			break;
		case SC_W:  
			printf("SC.W\n");
			cpu->regs[get_rd(inst)] = 0; // Success
			store_cpu(cpu, rs1_value, 32, rs2_value);
			break;
		case AMOSWAP_W:  
			printf("AMOSWAP.W\n");
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, rs2_value);
			break;
		case AMOADD_W:  
			printf("AMOADD.W\n");
			res = tmp + (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break; 
		case AMOXOR_W: 
			printf("AMOXOR.W\n");
			res = tmp ^ (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break;
		case AMOAND_W:  
			printf("AMOAND.W\n");
			res = tmp & (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break; 
		case AMOOR_W:  
			printf("AMOOR.W\n");
			res = tmp | (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break; 
		case AMOMIN_W:  
			printf("AMOMIN.W\n");
			res = ((int32_t)tmp < (int32_t)rs2_value) ? tmp : rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break;
		case AMOMAX_W: 
			printf("AMOMAX.W\n");
			res = ((int32_t)tmp > (int32_t)rs2_value) ? tmp : rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break;
		case AMOMINU_W:
			printf("AMOMINU.W\n");
			res = (tmp < rs2_value) ? tmp : rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break;
		case AMOMAXU_W:
			printf("AMOMAXU.W\n");
			res = (tmp > rs2_value) ? tmp : rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break;
		default:
			fprintf(stderr, "Unknown AMO instruction: funct7=0x%x\n", funct7);
			return;
	}
}

void exec_I_TYPE(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t funct3,  uint32_t imm_I)
{
	uint32_t rd_value = 0;
	uint32_t funct7 = GET_FUNCT7(inst);

	switch (funct3) {
		case ADDI: 
			printf("ADDI: rs1_value=0x%x, imm_I=0x%x\n", rs1_value, imm_I);
			rd_value = rs1_value + (int64_t) imm_I; 
			printf("ADDI result: 0x%x\n", rd_value);
    		printf("ADDI\n");
			break;
		case SLTI: 
    		rd_value = (rs1_value < (int64_t) imm_I)?1:0;
    		printf("SLTI\n");
			break;
		case SLTIU:
			rd_value = (rs1_value < (uint32_t)imm_I)?1:0;
    		printf("SLTIU\n");
			break;
		case XORI: 
			rd_value = rs1_value ^ imm_I; 
    		printf("XORI\n");
			break;
		case ORI:  
			rd_value = rs1_value | imm_I;
    		printf("ORI\n");
			break;
		case ANDI: 
			rd_value = rs1_value & imm_I;
    		printf("ANDI\n");
			break;
		case SLLI: 
			rd_value = rs1_value << get_shamt(inst); 
    		printf("SLLI\n");
			break;
		case SRI:
			if (funct7 == 0x00) {
				// SRLI
				rd_value = rs1_value >> get_shamt(inst);
				printf("SRLI\n");
			} else if (funct7 == 0x20) {
				// SRAI
				rd_value = (int32_t)rs1_value >> get_shamt(inst);
				printf("SRAI\n");
			}
			break;
		default:   fprintf(stderr, "未知的立即数运算指令: %x\n", inst); break;
	}

	set_reg_value_rd(cpu, inst, rd_value);
}

void exec_I_TYPE64(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t funct3,  uint32_t imm_I, uint32_t funct7 )
{
	uint64_t rd_value = 0;
	switch (funct3) {
		case ADDIW: 
			rd_value = (int64_t)(int32_t)(rs1_value + (int32_t)imm_I);
			printf("ADDIW\n");
			break;
		case SLLIW: 
			rd_value = (int64_t)(int32_t)(rs1_value << (get_shamt(inst) & 0x1f));
			printf("SLLIW\n");
			break;
		case SRIW : 
			switch (funct7) {
				case SRLIW: 
					rd_value = (int64_t)(int32_t)((uint32_t)rs1_value >> (get_shamt(inst) & 0x1f));
					printf("SRLIW\n");
					break;
				case SRAIW: 
					rd_value = (int64_t)(int32_t)(rs1_value >> (get_shamt(inst) & 0x1f));
					printf("SRAIW\n");
					break;
			} break;
	}
	set_reg_value_rd(cpu, inst, rd_value);
}

void exec_B_TYPE(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t rs2_value, uint64_t imm_B, uint32_t funct3)
{
	switch (funct3) {
		case BEQ:
			if (rs1_value == rs2_value) {
				cpu->pc = cpu->pc + imm_B - 4;
			}	
			printf("BEQ\n");
			break;
		case BNE:  
			if (rs1_value != rs2_value) {
				cpu->pc = cpu->pc + imm_B - 4;
			}
			printf("BNE\n");
			break;

		case BLT:  
			if (rs1_value < rs2_value) {
				cpu->pc = cpu->pc + imm_B - 4;
			}
			printf("BLT\n");
			break;

		case BGE:  
			if (rs1_value >= rs2_value) {
				cpu->pc = cpu->pc + imm_B - 4;
			}
			printf("BGE\n");
			break;
		case BLTU: 
			if ((uint64_t)rs1_value < (uint64_t)rs2_value) {
				cpu->pc = cpu->pc + (int64_t) imm_B - 4;
			}
			printf("BLTU\n");
			break;
		case BGEU: 
			if ((uint64_t)rs1_value >= (uint64_t)rs2_value) {
				cpu->pc = cpu->pc + (int64_t) imm_B - 4;
			}
			printf("BGEU\n");
			break;
		default:   fprintf(stderr, "未知的分支指令: %x\n", inst); break;
	}
}

void exec_S_TYPE(CPU *cpu, uint32_t inst, uint32_t rs1_value,  uint32_t rs2_value, uint64_t imm_S, uint32_t funct3)
{
	uint64_t addr = 0;
	int length = 0;
    addr = rs1_value + (int64_t) imm_S;

	switch (funct3) {
		case SB:   
			length = 8;
			break;

		case SH:   
			length = 16;
			if (ADDR_MISALIGNED(addr)) {
				fprintf(stderr, "SH: Address misaligned 0x%llx\n", addr);
				return;
			}
			break;

		case SW:   
			length = 32;
			if (ADDR_MISALIGNED(addr)) {
				fprintf(stderr, "SW: Address misaligned 0x%llx\n", addr);
				return;
			}
			break;
		case SD:   
			length = 64;
			if (ADDR_MISALIGNED_8(addr)) {
				fprintf(stderr, "SD: Address misaligned 0x%llx\n", addr);
				return;
			}
			break;
		default:   fprintf(stderr, "未知的存储指令: %x\n", inst); break;
	}
    store_cpu(cpu, addr, length, rs2_value);
}

void exec_LOAD(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t imm_I, uint32_t funct3)
{
	uint64_t rd_value = 0;
	uint64_t addr = rs1_value + (int64_t) imm_I;
	
	switch (funct3) {
		case LB:   
			rd_value = (int64_t)(int8_t)load_cpu(cpu, addr, 8);
			break;
		case LH:   
			if (ADDR_MISALIGNED(addr)) {
				fprintf(stderr, "LH: Address misaligned 0x%llx\n", addr);
				return;
			}
			rd_value = (int64_t)(int16_t)load_cpu(cpu, addr, 16);
			break;
		case LW:   
			if (ADDR_MISALIGNED(addr)) {
				fprintf(stderr, "LW: Address misaligned 0x%llx\n", addr);
				return;
			}
			rd_value = (int64_t)(int32_t)load_cpu(cpu, addr, 32);
			break;
		case LD:   
			if (ADDR_MISALIGNED_8(addr)) {
				fprintf(stderr, "LD: Address misaligned 0x%llx\n", addr);
				return;
			}
			rd_value = load_cpu(cpu, addr, 64);
			break;
		case LBU:  
			rd_value = load_cpu(cpu, addr, 8);
			break;
		case LHU: 
			if (ADDR_MISALIGNED(addr)) {
				fprintf(stderr, "LHU: Address misaligned 0x%llx\n", addr);
				return;
			}
			rd_value = load_cpu(cpu, addr, 16);
			break;
		case LWU: 
			if (ADDR_MISALIGNED(addr)) {
				fprintf(stderr, "LWU: Address misaligned 0x%llx\n", addr);
				return;
			}
			rd_value = load_cpu(cpu, addr, 32);
			break;
		default:   fprintf(stderr, "未知的加载指令: %x\n", inst); break;
	}
	cpu->regs[get_rd(inst)] = rd_value;
}

void exec_R_TYPE(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t rs2_value, uint32_t funct3, uint32_t funct7)
{
	uint32_t rd_value = 0;
	
	// Handle M-extension instructions (MUL, DIV, REM) first
	if (funct3 == 0x0 && funct7 == 0x01) {
		// MUL instruction
		rd_value = rs1_value * rs2_value;
		printf("MUL\n");
		set_reg_value_rd(cpu, inst, rd_value);
		return;
	} else if (funct3 == 0x4 && funct7 == 0x01) {
		// DIV instruction
		if (rs2_value != 0) {
			rd_value = (int32_t)rs1_value / (int32_t)rs2_value;
		} else {
			rd_value = 0xFFFFFFFF; // -1 for division by zero
		}
		printf("DIV\n");
		set_reg_value_rd(cpu, inst, rd_value);
		return;
	} else if (funct3 == 0x5 && funct7 == 0x01) {
		// DIVU instruction
		if (rs2_value != 0) {
			rd_value = (uint32_t)rs1_value / (uint32_t)rs2_value;
		} else {
			rd_value = 0xFFFFFFFF; // -1 for division by zero
		}
		printf("DIVU\n");
		set_reg_value_rd(cpu, inst, rd_value);
		return;
	} else if (funct3 == 0x6 && funct7 == 0x01) {
		// REM instruction
		if (rs2_value != 0) {
			rd_value = (int32_t)rs1_value % (int32_t)rs2_value;
		} else {
			rd_value = (int32_t)rs1_value; // remainder is dividend for division by zero
		}
		printf("REM\n");
		set_reg_value_rd(cpu, inst, rd_value);
		return;
	} else if (funct3 == 0x7 && funct7 == 0x01) {
		// REMU instruction
		if (rs2_value != 0) {
			rd_value = (uint32_t)rs1_value % (uint32_t)rs2_value;
		} else {
			rd_value = (uint32_t)rs1_value; // remainder is dividend for zero
		}
		printf("REMU\n");
		set_reg_value_rd(cpu, inst, rd_value);
		return;
	}
	
	switch (funct3) {
		case ADD:
			if (funct7 == 0) {
				printf("ADD: rs1_value=0x%x, rs2_value=0x%x\n", rs1_value, rs2_value);
				rd_value = rs1_value + rs2_value;
				printf("ADD result: 0x%x\n", rd_value);
				printf("ADD\n");
			} else if (funct7 == 0x20) {
				rd_value = rs1_value - rs2_value;
				printf("SUB\n");
			}
			break;

		case SLL: 
			rd_value = rs1_value << (rs2_value & 0x1f);
			printf("SLL\n");
			break;

		case SLT: 
			rd_value = rs1_value < (int64_t)rs2_value ? 1:0;
			printf("SLT\n");
			break;

		case SLTU:
			rd_value = (uint64_t)rs1_value < (uint64_t)rs2_value ? 1:0;
			printf("SLTU\n");
			break;

		case XOR: 
			rd_value = rs1_value ^ rs2_value;
			printf("XOR\n");
			break;

		case SR:
			if (funct7 == 0x20) {
				// SRA
				rd_value = (int32_t)rs1_value >> (rs2_value & 0x1f);
				printf("SRA\n");
			} else {
			 	// SRL
			 	rd_value = rs1_value >> (rs2_value & 0x1f);
				printf("SRL\n");
			}
			break;

		case OR:  
			rd_value = rs1_value | rs2_value;
			printf("OR\n");
			break;

		case AND: 
			rd_value = rs1_value & rs2_value;
			printf("AND\n");
			break;

		default:   fprintf(stderr, "未知的运算指令: %x\n", inst); break;
	}

	set_reg_value_rd(cpu, inst, rd_value);
}

void exec_R_TYPE64(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t rs2_value, uint32_t funct3, uint32_t funct7)
{
	uint64_t rd_value = 0;
	switch (funct3) {
		case ADDSUB:
			switch (funct7) {
				case ADDW:  
					rd_value = (int64_t)(int32_t)(rs1_value + rs2_value);
					printf("ADDW\n");
					break;
				case SUBW: 
					rd_value = (int64_t)(int32_t)(rs1_value - rs2_value);
					printf("SUBW\n");
					break;
				case MULW:  
					rd_value = (int64_t)(int32_t)(rs1_value * rs2_value);
					printf("MULW\n");
					break;
			} break;
		case DIVW:  
			if (rs2_value != 0) {
				rd_value = (int64_t)(int32_t)(rs1_value / rs2_value);
			} else {
				rd_value = 0xFFFFFFFF; // -1 for division by zero
			}
			printf("DIVW\n");
			break;
		case SLLW:  
			rd_value = (int64_t)(int32_t)(rs1_value << (rs2_value & 0x1f));
			printf("SLLW\n");
			break;
		case SRW:
			switch (funct7) {
				case SRLW:  
					rd_value = (int64_t)(int32_t)((uint32_t)rs1_value >> (rs2_value & 0x1f));
					printf("SRLW\n");
					break;
				case SRAW:  
					rd_value = (int64_t)(int32_t)(rs1_value >> (rs2_value & 0x1f));
					printf("SRAW\n");
					break;
				case DIVUW: 
					if (rs2_value != 0) {
						rd_value = (int64_t)(int32_t)((uint32_t)rs1_value / (uint32_t)rs2_value);
					} else {
						rd_value = 0xFFFFFFFF; // -1 for division by zero
					}
					printf("DIVUW\n");
					break;
			} break;
		case REMW:  
			if (rs2_value != 0) {
				rd_value = (int64_t)(int32_t)(rs1_value % rs2_value);
			} else {
				rd_value = (int64_t)(int32_t)rs1_value; // remainder is dividend for division by zero
			}
			printf("REMW\n");
			break;
		case REMUW: 
			if (rs2_value != 0) {
				rd_value = (int64_t)(int32_t)((uint32_t)rs1_value % (uint32_t)rs2_value);
			} else {
				rd_value = (int64_t)(int32_t)rs1_value; // remainder is dividend for division by zero
			}
			printf("REMUW\n");
			break;
		default: 
			fprintf(stderr, "未知的64位运算指令: %x\n", inst); 
			break;
	}
	set_reg_value_rd(cpu, inst, rd_value);
}

int cpu_execute(CPU *cpu, uint32_t inst) 
{
	// 检查是否是压缩指令 (16位，且最低两位不为 11)
	if (inst <= 0xFFFF && (inst & 0x3) != 0x3) {
		return execute_compressed(cpu, (uint16_t)inst);
	}
	
	int opcode = inst & 0x7f; // opcode 在位 6..0
	int funct3 = (inst >> 12) & 0x7; // funct3 在位 14..12
	int funct7 = (inst >> 25) & 0x7f; // funct7 在位 31..25

	cpu->regs[0] = 0; // x0 硬连接到 0

	printf("# cpu execute inst: 0x%08x, opcode: 0x%02x\n", inst, opcode); // 调试输出
	dump_instruction(inst); 

	switch (opcode) {
		case LUI:   
			exec_LUI(cpu, inst); 
			break;

		case AUIPC: 
			exec_AUIPC(cpu, inst); 
			break;

		case JAL:   
			exec_JAL(cpu, inst); 
			break;

		case JALR:  
			exec_JALR(cpu, inst); 
			break;

		case OPCODE_BRANCH: // 分支指令
			exec_B_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst), get_imm_B(inst), funct3);
			break;

		case OPCODE_LOAD: // 加载指令
			exec_LOAD(cpu, inst, get_reg_value_rs1(cpu, inst), get_imm_I(inst), funct3);
			break;

		case OPCODE_STORE: // 存储指令
			exec_S_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst),  get_reg_value_rs2(cpu, inst), get_imm_S(inst), funct3);
			break;

		case OPCODE_OP_IMM: // 立即数运算指令
			exec_I_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst), funct3,  get_imm_I(inst));
			break;

		case OPCODE_OP: // 运算指令
			exec_R_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst), funct3,  funct7);
			break;

        case OPCODE_FENCE: 
			exec_FENCE(cpu, inst, funct3);
			break;

        case OPCODE_OP_IMM_32:
			exec_I_TYPE64(cpu, inst, get_reg_value_rs1(cpu, inst), funct3,  get_imm_I(inst), funct7);
			break;

        case OPCODE_OP_32:
			exec_R_TYPE64(cpu, inst, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst), funct3,  funct7);
            break;

        case OPCODE_SYSTEM:
			exec_CSR(cpu, inst, funct3, get_imm_I(inst)); 
            break;

        case OPCODE_AMO:
			exec_AMO_W(cpu, inst, funct3, funct7, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst));
            break;

		default:
			fprintf(stderr, "[-] 错误 -> opcode:0x%x, funct3:0x%x, funct7:0x%x\n", opcode, funct3, funct7);
			return 0;
	}
	return 1;
}

// 压缩指令执行函数
int execute_compressed(CPU *cpu, uint16_t inst) 
{
	printf("# cpu execute compressed inst: 0x%04x\n", inst);
	
	// 压缩指令格式
	uint8_t opcode = inst & 0x3;
	uint8_t funct3 = (inst >> 13) & 0x7;
	uint8_t funct4 = (inst >> 12) & 0xF;
	uint8_t funct6 = (inst >> 10) & 0x3F;
	
	// 寄存器字段
	uint8_t rd = ((inst >> 7) & 0x1) | ((inst >> 2) & 0x1E);
	uint8_t rs1 = ((inst >> 7) & 0x1) | ((inst >> 2) & 0x1E);
	uint8_t rs2 = ((inst >> 2) & 0x1F);
	
	// 立即数字段
	int16_t imm_5 = ((inst >> 2) & 0x1F);
	int16_t imm_6 = ((inst >> 2) & 0x3F);
	int16_t imm_8 = ((inst >> 2) & 0xFF);
	int16_t imm_9 = ((inst >> 2) & 0x1FF);
	int16_t imm_10 = ((inst >> 2) & 0x3FF);
	int16_t imm_11 = ((inst >> 2) & 0x7FF);
	int16_t imm_12 = ((inst >> 2) & 0xFFF);
	
	// 符号扩展
	if (imm_5 & 0x10) imm_5 |= 0xFFE0;
	if (imm_6 & 0x20) imm_6 |= 0xFFC0;
	if (imm_8 & 0x80) imm_8 |= 0xFF00;
	if (imm_9 & 0x100) imm_9 |= 0xFE00;
	if (imm_10 & 0x200) imm_10 |= 0xFC00;
	if (imm_11 & 0x400) imm_11 |= 0xF800;
	if (imm_12 & 0x800) imm_12 |= 0xF000;
	
	switch (opcode) {
		case 0x0: // C.ADDI4SPN, C.LW, C.SW, C.LD, C.SD, C.FLW, C.FSW, C.FLD, C.FSD
			switch (funct3) {
				case 0x0: // C.ADDI4SPN
					if (inst != 0) { // 不是 NOP
						uint16_t nzuimm = ((inst >> 5) & 0x3C) | ((inst >> 7) & 0x40) | ((inst >> 6) & 0x80);
						cpu->regs[rd] = cpu->regs[2] + nzuimm; // x2 is sp
						printf("C.ADDI4SPN: sp + %d -> x%d\n", nzuimm, rd);
					}
					break;
				case 0x2: // C.LW
					{
						uint16_t offset = ((inst >> 6) & 0x7) | ((inst >> 10) & 0x38);
						uint64_t addr = cpu->regs[rs1] + offset;
						cpu->regs[rd] = (int32_t)bus_load(&cpu->bus, addr, 32);
						printf("C.LW: [x%d+%d] -> x%d\n", rs1, offset, rd);
					}
					break;
				default:
					printf("Unsupported C0 instruction: funct3=0x%x\n", funct3);
					return 0;
			}
			break;
			
		case 0x1: // C.ADDI, C.JAL, C.LI, C.LUI, C.ADDI16SP, C.SRLI, C.SRAI, C.ANDI, C.SUB, C.XOR, C.OR, C.AND, C.J, C.BEQZ, C.BNEZ
			switch (funct3) {
				case 0x0: // C.ADDI
					if (rd != 0) {
						cpu->regs[rd] = cpu->regs[rd] + imm_6;
						printf("C.ADDI: x%d + %d -> x%d\n", rd, imm_6, rd);
					}
					break;
				case 0x1: // C.JAL
					cpu->regs[1] = cpu->pc + 2; // ra = x1
					cpu->pc = cpu->pc + imm_11;
					printf("C.JAL: pc + %d -> pc, ra = pc + 2\n", imm_11);
					return 1; // 跳转，不增加 PC
				case 0x2: // C.LI
					if (rd != 0) {
						cpu->regs[rd] = imm_6;
						printf("C.LI: %d -> x%d\n", imm_6, rd);
					}
					break;
				case 0x3: // C.LUI
					if (rd != 0 && rd != 2) { // 不能是 x0 或 x2
						cpu->regs[rd] = imm_6 << 12;
						printf("C.LUI: %d << 12 -> x%d\n", imm_6, rd);
					}
					break;
				case 0x4: // C.ADDI16SP
					if (rd == 2) { // 只能是 sp
						uint16_t nzimm = ((inst >> 6) & 0x1) | ((inst >> 7) & 0x1E) | ((inst >> 8) & 0x20) | ((inst >> 9) & 0x40) | ((inst >> 10) & 0x80);
						if (nzimm != 0) {
							cpu->regs[2] = cpu->regs[2] + (nzimm << 4);
							printf("C.ADDI16SP: sp + %d -> sp\n", nzimm << 4);
						}
					}
					break;
				case 0x5: // C.SRLI, C.SRAI
					{
						uint8_t shamt = (inst >> 6) & 0x1F;
						if (shamt != 0) {
							if ((inst >> 10) & 0x1) { // C.SRAI
								cpu->regs[rd] = (int32_t)cpu->regs[rd] >> shamt;
								printf("C.SRAI: x%d >> %d -> x%d\n", rd, shamt, rd);
							} else { // C.SRLI
								cpu->regs[rd] = cpu->regs[rd] >> shamt;
								printf("C.SRLI: x%d >> %d -> x%d\n", rd, shamt, rd);
							}
						}
					}
					break;
				case 0x6: // C.ANDI
					cpu->regs[rd] = cpu->regs[rd] & imm_6;
					printf("C.ANDI: x%d & %d -> x%d\n", rd, imm_6, rd);
					break;
				case 0x7: // C.SUB, C.XOR, C.OR, C.AND
					{
						uint8_t funct2 = (inst >> 10) & 0x3;
						switch (funct2) {
							case 0x0: // C.SUB
								cpu->regs[rd] = cpu->regs[rd] - cpu->regs[rs2];
								printf("C.SUB: x%d - x%d -> x%d\n", rd, rs2, rd);
								break;
							case 0x1: // C.XOR
								cpu->regs[rd] = cpu->regs[rd] ^ cpu->regs[rs2];
								printf("C.XOR: x%d ^ x%d -> x%d\n", rd, rs2, rd);
								break;
							case 0x2: // C.OR
								cpu->regs[rd] = cpu->regs[rd] | cpu->regs[rs2];
								printf("C.OR: x%d | x%d -> x%d\n", rd, rs2, rd);
								break;
							case 0x3: // C.AND
								cpu->regs[rd] = cpu->regs[rd] & cpu->regs[rs2];
								printf("C.AND: x%d & x%d -> x%d\n", rd, rs2, rd);
								break;
						}
					}
					break;
			}
			break;
			
		case 0x2: // C.SLLI, C.LWSP, C.JR, C.MV, C.EBREAK, C.JALR, C.ADD
			switch (funct3) {
				case 0x0: // C.SLLI
					{
						uint8_t shamt = (inst >> 6) & 0x1F;
						if (shamt != 0) {
							cpu->regs[rd] = cpu->regs[rd] << shamt;
							printf("C.SLLI: x%d << %d -> x%d\n", rd, shamt, rd);
						}
					}
					break;
				case 0x2: // C.LWSP
					if (rd != 0) {
						uint16_t offset = ((inst >> 4) & 0x3C) | ((inst >> 9) & 0x40);
						uint64_t addr = cpu->regs[2] + offset; // sp
						cpu->regs[rd] = (int32_t)bus_load(&cpu->bus, addr, 32);
						printf("C.LWSP: [sp+%d] -> x%d\n", offset, rd);
					}
					break;
				case 0x4: // C.JR, C.MV
					if ((inst >> 12) & 0x1) { // C.JR
						if (rs1 != 0) {
							cpu->pc = cpu->regs[rs1];
							printf("C.JR: x%d -> pc\n", rs1);
							return 1; // 跳转，不增加 PC
						}
					} else { // C.MV
						if (rd != 0) {
							cpu->regs[rd] = cpu->regs[rs2];
							printf("C.MV: x%d -> x%d\n", rs2, rd);
						}
					}
					break;
				case 0x6: // C.EBREAK, C.JALR
					if ((inst >> 12) & 0x1) { // C.JALR
						if (rs1 != 0) {
							uint64_t target = cpu->regs[rs1];
							cpu->regs[1] = cpu->pc + 2; // ra = x1
							cpu->pc = target;
							printf("C.JALR: x%d -> pc, ra = pc + 2\n", rs1);
							return 1; // 跳转，不增加 PC
						}
					} else { // C.EBREAK
						printf("C.EBREAK: breakpoint\n");
						return 0; // 停止执行
					}
					break;
				case 0x7: // C.ADD
					if (rd != 0) {
						cpu->regs[rd] = cpu->regs[rd] + cpu->regs[rs2];
						printf("C.ADD: x%d + x%d -> x%d\n", rd, rs2, rd);
					}
					break;
			}
			break;
			
		default:
			printf("Unsupported compressed instruction: opcode=0x%x\n", opcode);
			return 0;
	}
	
	return 1;
}


