#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cpu.h"

/* https://five-embeddev.com/riscv-user-isa-manual/Priv-v1.12/instr-table.html */

#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[31m"
#define ANSI_RESET   "\x1b[0m"

#define ADDR_MISALIGNED(addr) (addr & 0x3)

uint64_t load8(DRAM* dram, uint64_t addr) 
{
	return (uint64_t) dram->mem[addr - DRAM_BASE];
}

uint64_t load16(DRAM* dram, uint64_t addr) 
{
	return (uint64_t) dram->mem[addr - DRAM_BASE]
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 1] << 8);
}

uint64_t load32(DRAM* dram, uint64_t addr) 
{
	return (uint64_t) dram->mem[addr - DRAM_BASE]
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 1] << 8)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 2] << 16)
		| ((uint64_t) dram->mem[addr - DRAM_BASE + 3] << 24);
}

uint64_t load64(DRAM* dram, uint64_t addr) 
{
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
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
}

void store16(DRAM* dram, uint64_t addr, uint64_t value) 
{
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
	dram->mem[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
}

void store32(DRAM* dram, uint64_t addr, uint64_t value) 
{
	dram->mem[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
	dram->mem[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
	dram->mem[addr - DRAM_BASE + 2] = (uint8_t) ((value >> 16) & 0xff);
	dram->mem[addr - DRAM_BASE + 3] = (uint8_t) ((value >> 24) & 0xff);
}

void store64(DRAM* dram, uint64_t addr, uint64_t value) 
{
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

void cpu_init(CPU *cpu) 
{
	cpu->regs[0] = 0x00; // Register x0 hardwired to 0
	cpu->regs[2] = DRAM_BASE + DRAM_SIZE; // Set stack pointer
	cpu->pc = DRAM_BASE; // Set program counter to the base address
}

uint32_t cpu_fetch(CPU *cpu) 
{
	return bus_load(&(cpu->bus), cpu->pc, 32);
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

	for (int i = 0; i < 8; i++) {
		printf("   %4s: %#-13.2lx  ", abi[i], cpu->regs[i]);
		printf("   %2s: %#-13.2lx  ", abi[i + 8], cpu->regs[i + 8]);
		printf("   %2s: %#-13.2lx  ", abi[i + 16], cpu->regs[i + 16]);
		printf("   %3s: %#-13.2lx\n", abi[i + 24], cpu->regs[i + 24]);
	}
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
    cpu->pc = (get_reg_value_rs1(cpu, inst) + (int64_t) imm) & 0xfffffffe;
    cpu->regs[get_rd(inst)] = tmp;
    /*print_op("NEXT -> %#lx, imm:%#lx\n", cpu->pc, imm);*/
    print_op("jalr\n");
    if (ADDR_MISALIGNED(cpu->pc)) {
        fprintf(stderr, "JAL pc address misalligned");
        exit(0);
    }
}

// CSR instructions
void exec_CSR(CPU* cpu, uint32_t inst, uint32_t funct3, uint32_t imm_I) 
{
	switch (funct3) {
		case ECALLBREAK:    
			if (imm_I == 0x0)
				break;
			if (imm_I == 0x1)
				break;
			break;
		case CSRRW  :  
    		cpu->regs[get_rd(inst)] = csr_read(cpu, get_csr(inst));
    		csr_write(cpu, get_csr(inst), cpu->regs[get_rs1(inst)]);
			break;
		case CSRRS  :  
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] | cpu->regs[get_rs1(inst)]);
			break;
		case CSRRC  :  
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] & !(cpu->regs[get_rs1(inst)]) );
			break;
		case CSRRWI :  
    		csr_write(cpu, get_csr(inst), get_rs1(inst));
			break;
		case CSRRSI :  
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] | get_rs1(inst));
			break;
		case CSRRCI :   
    		csr_write(cpu, get_csr(inst), cpu->csr[get_csr(inst)] & !get_rs1(inst));
			break; 
		default:
			return ;
	}
}

// AMO_W
void exec_AMO_W(CPU *cpu, uint32_t inst, uint32_t funct3, uint32_t funct7, uint32_t rs1_value, uint32_t rs2_value)
{
	uint32_t tmp = load_cpu(cpu, rs1_value, 32);
	uint32_t res = 0;
	switch (funct7 >> 2) { 
		case LR_W      : 
		case SC_W      :  
		case AMOSWAP_W :  
			break;
		case AMOADD_W  :  
			res = tmp + (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break; 
		case AMOXOR_W  : 
			res = tmp ^ (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break;
		case AMOAND_W  :  

			res = tmp & (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break; 
		case AMOOR_W   :  
			res = tmp | (uint32_t)rs2_value;
			cpu->regs[get_rd(inst)] = tmp;
			store_cpu(cpu, rs1_value, 32, res);
			break; 
		case AMOMIN_W  :  
		case AMOMAX_W  : 
		case AMOMINU_W :
		case AMOMAXU_W :
			break;
		default:
			return;
	}
}

void exec_I_TYPE(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t funct3,  uint32_t imm_I)
{
	uint32_t rd_value = 0;

	switch (funct3) {
		case ADDI: 
			rd_value = rs1_value + (int64_t) imm_I; 
    		printf("ADDI\n");
			break;
		case SLTI: 
    		rd_value = (rs1_value < (int64_t) imm_I)?1:0;
    		printf("SLTI\n");
			break;
		case SLTIU:
			rd_value = (cpu->regs[get_rs1(inst)] < imm_I)?1:0;
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
				   //case SRLI: exec_SRLI(cpu, inst); break;
		case SRAI: 
			rd_value = rs1_value >> imm_I;
    		printf("SRAI\n");
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
			rd_value = rs1_value + (int64_t)imm_I;
			break;
		case SLLIW: 
			rd_value  = (int64_t)rs1_value <<  get_shamt(inst);
			break;
		case SRIW : 
			switch (funct7) {
				case SRLIW: 
					rd_value = (int64_t)rs1_value >> get_shamt(inst);
					break;
				case SRAIW: 
					rd_value = (int64_t)rs1_value >> imm_I;
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
			if (rs1_value < rs2_value) {
				cpu->pc = cpu->pc + (int64_t) imm_B - 4;
			}
			printf("BLTU\n");
			break;
		case BGEU: 
			if (rs1_value >= rs2_value) {
				cpu->pc = cpu->pc + (int64_t) imm_B - 4;
			}
			printf("BGEU\n");
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
			break;

		case SW:   
			length = 32;
		default:   fprintf(stderr, "未知的存储指令: %x\n", inst); break;
	}
    store_cpu(cpu, addr, length, rs2_value);
}

void exec_LOAD(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t imm_I, uint32_t funct3)
{
	uint32_t rd_value = 0;
	switch (funct3) {
		case LB:   
			rd_value = load_cpu(cpu, rs1_value + (int64_t ) imm_I, 8);
			break;
		case LH:   
			rd_value = load_cpu(cpu, rs1_value + (int64_t ) imm_I, 16);
			break;
		case LW:   
			rd_value = load_cpu(cpu, rs1_value + (int64_t ) imm_I, 32);
			break;
		case LBU:  
			rd_value = load_cpu(cpu, rs1_value + (uint64_t ) imm_I, 8);
			break;
		case LHU: 
			rd_value = load_cpu(cpu, rs1_value + (uint64_t ) imm_I, 16);
			break;
		default:   fprintf(stderr, "未知的加载指令: %x\n", inst); break;
	}
	set_reg_value_rd(cpu, inst, rd_value);
}

void exec_R_TYPE(CPU *cpu, uint32_t inst, uint32_t rs1_value, uint32_t rs2_value, uint32_t funct3, uint32_t funct7)
{
	uint32_t rd_value = 0;
	switch (funct3) {
		case ADD:
			if (funct7 == 0) {
				rd_value = rs1_value + rs2_value;
			} else if (funct7 == 0x20) {
				rd_value = rs1_value - rs2_value;
			}
			break;

		case SLL: 
			rd_value = rs1_value << rs2_value;
			break;

		case SLT: 
			rd_value = rs1_value < (int64_t)rs2_value ? 1:0;
			break;

		case SLTU:
			rd_value = rs1_value < rs2_value ? 1:0;
			break;

		case XOR: 
			rd_value = rs1_value ^ rs2_value;
			break;

		case SR:
			if (funct7 == 0x20) {
				// SRA
				rd_value = (int32_t)rs1_value >> rs2_value;
			} else {
			 	// SRL
			 	rd_value = rs1_value >> rs2_value;
			}
			break;

		case OR:  
			rd_value = rs1_value | rs2_value;
			break;

		case AND: 
			rd_value = rs1_value & rs2_value;
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
					rd_value = rs1_value + rs2_value;
					break;
				case SUBW: 
					rd_value = rs1_value - rs2_value;
					break;
				case MULW:  
					rd_value = rs1_value * rs2_value;
					break;
			} break;
		case DIVW:  
			rd_value = rs1_value / rs2_value;
			break;
		case SLLW:  
			rd_value = rs1_value << rs2_value;
			break;
		case SRW:
					switch (funct7) {
						case SRLW:  
							rd_value = rs1_value >> rs2_value;
							break;
						case SRAW:  
							rd_value = rs1_value >> rs2_value;
							break;
						case DIVUW: 
							rd_value = rs1_value / rs2_value;
							break;
					} break;
		case REMW:  
			rd_value = rs1_value % rs2_value;
			break;
		case REMUW: 
			rd_value = rs1_value % rs2_value;
			break;
		default: ;
	}
	set_reg_value_rd(cpu, inst, rd_value);
}

int cpu_execute(CPU *cpu, uint32_t inst) 
{
	int opcode = inst & 0x7f; // opcode 在位 6..0
	int funct3 = (inst >> 12) & 0x7; // funct3 在位 14..12
	int funct7 = (inst >> 25) & 0x7f; // funct7 在位 31..25

	cpu->regs[0] = 0; // x0 硬连接到 0

	printf("%s\n%#.8lx -> %s", ANSI_YELLOW, cpu->pc - 4, ANSI_RESET); // 调试输出

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
			break; // 添加 JALR 指令处理

		case B_TYPE: // 分支指令
			exec_B_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst), get_imm_B(inst), funct3);
			break;

		case LOAD: // 加载指令
			exec_LOAD(cpu, inst, get_reg_value_rs1(cpu, inst), get_imm_I(inst), funct3);
			break;

		case S_TYPE: // 存储指令
			exec_S_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst),  get_reg_value_rs2(cpu, inst), get_imm_S(inst), funct3);
			break;

		case I_TYPE: // 立即数运算指令
			exec_I_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst), funct3,  get_imm_I(inst));
			break;

		case R_TYPE: // 运算指令
			exec_R_TYPE(cpu, inst, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst), funct3,  funct7);
			break;

        case FENCE: 
			break;

        case I_TYPE_64:
			exec_I_TYPE64(cpu, inst, get_reg_value_rs1(cpu, inst), funct3,  get_imm_I(inst), funct7);
			break;

        case R_TYPE_64:
			exec_R_TYPE64(cpu, inst, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst), funct3,  funct7);
            break;

        case CSR:
			exec_CSR(cpu, inst, funct3, get_imm_I(inst)); 
            break;

        case AMO_W:
			exec_AMO_W(cpu, inst, funct3, funct7, get_reg_value_rs1(cpu, inst), get_reg_value_rs2(cpu, inst));
            break;

        //case 0x00:
         //   return 0;


		default:
			fprintf(stderr, "[-] 错误 -> opcode:0x%x, funct3:0x%x, funct7:0x%x\n", opcode, funct3, funct7);
			return 0;
	}
	return 1;
}


