#ifndef CPU_H
#define CPU_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>



#define TRUE 1
#define FALSE 0

#define DRAM_SIZE 1024*1024*1
#define DRAM_BASE 0x80000000ULL

typedef struct DRAM {
	uint8_t mem[DRAM_SIZE];     // Dram memory of DRAM_SIZE
} DRAM;

uint64_t dram_load(DRAM* dram, uint64_t addr, uint64_t size);

void dram_store(DRAM* dram, uint64_t addr, uint64_t size, uint64_t value);

uint64_t load(DRAM* dram, uint64_t addr, uint64_t size);

void store(DRAM* dram, uint64_t addr, uint64_t size, uint64_t value);


typedef struct BUS {
    struct DRAM dram;
} BUS;

uint64_t bus_load(BUS* bus, uint64_t addr, uint64_t size);
void bus_store(BUS* bus, uint64_t addr, uint64_t size, uint64_t value);

typedef struct CPU {
    uint64_t regs[32];          // 32 64-bit registers (x0-x31)
    uint64_t pc;                // 64-bit program counter
    uint64_t csr[4069];
    struct BUS bus;             // CPU connected to BUS
} CPU;

void cpu_init(struct CPU *cpu);
uint32_t cpu_fetch(struct CPU *cpu);
int cpu_execute(struct CPU *cpu, uint32_t inst);
int execute_compressed(struct CPU *cpu, uint16_t inst);
void dump_registers(struct CPU *cpu); 
void dump_instruction(uint32_t inst);
void debug_print(const char* format, ...);
void dump_memory(DRAM* dram, uint64_t addr, uint64_t size);

//      Name        Number   Priv       Description
//------------------------------------------------------------------------------------

// User Trap Setup
#define USTATUS     0x000 // URW User status register.
#define UIE         0x004 // URW User interrupt-enable register.
#define UTVEC       0x005 // URW User trap handler base address.

//User Trap Handling
#define USCRATCH    0x040 // URW Scratch register for user trap handlers.
#define UEPC        0x041 // URW User exception program counter.
#define UCAUSE      0x042 // URW User trap cause.
#define UTVAL       0x043 // URW User bad address or instruction.
#define UIP         0x044 // URW User interrupt pending.

//User Floating-Point CSRs
#define FFLAGS      0x001 // URW Floating-Point Accrued Exceptions.
#define FRM         0x002 // URW Floating-Point Dynamic Rounding Mode.
#define FCSR        0x003 // URW Floating-Point Control and Status Register (frm + fflags)

//User Counter/Timers
#define CYCLE       0xC00 // URO Cycle counter for RDCYCLE instruction.
#define TIME        0xC01 // URO Timer for RDTIME instruction.
#define INSTRET     0xC02 // URO Instructions-retired counter for RDINSTRET instruction.
#define HPMCOUNTER3 0xC03 // URO Performance-monitoring counter.
#define HPMCOUNTER4 0xC04 // URO Performance-monitoring counter.
// ... hpm counter 4-31 (TODO)
#define HPMCOUNTER31 0xC1F // URO Performance-monitoring counter.
#define CYCLEH      0xC80  // URO Upper 32 bits of cycle, RV32I only.
#define TIMEH       0xC81  // URO Upper 32 bits of time, RV32I only.
#define INSTRETH    0xC82  // URO Upper 32 bits of instret, RV32I only.
#define HPMCOUNTER3H 0xC83 // URO Upper 32 bits of hpmcounter3, RV32I only.
#define HPMCOUNTER4H 0xC84 // URO Upper 32 bits of hpmcounter4, RV32I only.
// ... hpm counter 4-31 (TODO)
#define HPMCOUNTER31H 0xC9F // URO Upper 32 bits of hpmcounter31, RV32I only.


//Supervisor Trap Setup
#define SSTATUS     0x100 // SRW Supervisor status register.
#define SEDELEG     0x102 // SRW Supervisor exception delegation register.
#define SIDELEG     0x103 // SRW Supervisor interrupt delegation register.
#define SIE         0x104 // SRW Supervisor interrupt-enable register.
#define STVEC       0x105 // SRW Supervisor trap handler base address.
#define SCOUNTEREN  0x106 // SRW Supervisor counter enable.

//Supervisor Trap Handling
#define SSCRATCH    0x140 // SRW Scratch register for supervisor trap handlers.
#define SEPC        0x141 // SRW Supervisor exception program counter.
#define SCAUSE      0x142 // SRW Supervisor trap cause.
#define STVAL       0x143 // SRW Supervisor bad address or instruction.
#define SIP         0x144 // SRW Supervisor interrupt pending.

//Supervisor Protection and Translation
#define SATP        0x180 // SRW Supervisor address translation and protection.

//Machine Information Registers
#define MVENDORID   0xF11 // MRO Vendor ID.
#define MARCHID     0xF12 // MRO Architecture ID.
#define MIMPID      0xF13 // MRO Implementation ID.
#define MHARTID     0xF14 // MRO Hardware thread ID.

//Machine Trap Setup
#define MSTATUS     0x300 // MRW Machine status register.
#define MISA        0x301 // MRW ISA and extensions
#define MEDELEG     0x302 // MRW Machine exception delegation register.
#define MIDELEG     0x303 // MRW Machine interrupt delegation register.
#define MIE         0x304 // MRW Machine interrupt-enable register.
#define MTVEC       0x305 // MRW Machine trap-handler base address.
#define MCOUNTEREN  0x306 // MRW Machine counter enable.

//Machine Trap Handling
#define MSCRATCH    0x340 // MRW Scratch register for machine trap handlers.
#define MEPC        0x341 // MRW Machine exception program counter.
#define MCAUSE      0x342 // MRW Machine trap cause.
#define MTVAL       0x343 // MRW Machine bad address or instruction.
#define MIP         0x344 // MRW Machine interrupt pending.

//Machine Memory Protection
#define PMPCFG0     0x3A0 // MRW Physical memory protection configuration.
#define PMPCFG1     0x3A1 // MRW Physical memory protection configuration, RV32 only.
#define PMPCFG2     0x3A2 // MRW Physical memory protection configuration.
#define PMPCFG3     0x3A3 // MRW Physical memory protection configuration, RV32 only.
#define PMPADDR0    0x3B0 // MRW Physical memory protection address register.
#define PMPADDR1    0x3B1 // MRW Physical memory protection address register.
// ... 2-15 /TODO
#define PMPADDR15   0x3BF // MRW Physical memory protection address register.

//Machine Counter/Timers
#define MCYCLE       0xB00 // MRW Machine cycle counter.
#define MINSTRET     0xB02 // MRW Machine instructions-retired counter.
#define MHPMCOUNTER3 0xB03 // MRW Machine performance-monitoring counter.
#define MHPMCOUNTER4 0xB04 // MRW Machine performance-monitoring counter.
// #define ...
#define MHPMCOUNTER31 0xB1F // MRW Machine performance-monitoring counter.
#define MCYCLEH       0xB80 // MRW Upper 32 bits of mcycle, RV32I only.
#define MINSTRETH     0xB82 // MRW Upper 32 bits of minstret, RV32I only.
#define MHPMCOUNTER3H 0xB83 // MRW Upper 32 bits of mhpmcounter3, RV32I only.
#define MHPMCOUNTER4H 0xB84 // MRW Upper 32 bits of mhpmcounter4, RV32I only.
// ...
#define MHPMCOUNTER31H 0xB9F // MRW Upper 32 bits of mhpmcounter31, RV32I only.

//Machine Counter Setup
#define MCOUNTINHIBIT 0x320 // MRW Machine counter-inhibit register.
#define MHPMEVENT3    0x323 // MRW Machine performance-monitoring event selector.
#define MHPMEVENT4    0x324 // MRW Machine performance-monitoring event selector.
//#define ...
#define MHPMEVENT31 0x33F // MRW Machine performance-monitoring event selector.

//Debug/Trace Registers (shared with Debug Mode)
#define TSELECT     0x7A0 // MRW Debug/Trace trigger register select.
#define TDATA1      0x7A1 // MRW First Debug/Trace trigger data register.
#define TDATA2      0x7A2 // MRW Second Debug/Trace trigger data register.
#define TDATA3      0x7A3 // MRW Third Debug/Trace trigger data register.

//Debug Mode Registers
#define DCSR        0x7B0 // DRW Debug control and status register.
#define DPC         0x7B1 // DRW Debug PC.
#define DSCRATCH0   0x7B2 // DRW Debug scratch register 0.
#define DSCRATCH1   0x7B3 // DRW Debug scratch register 1.


// functions

uint64_t csr_read(CPU* cpu, uint64_t csr);
void csr_write(CPU* cpu, uint64_t csr, uint64_t value);

#define LUI     0x37 
#define AUIPC   0x17 

#define JAL     0x6f 
#define JALR    0x67 

#define BRANCH  0x63
    #define BEQ     0x0
    #define BNE     0x1
    #define BLT     0x4
    #define BGE     0x5
    #define BLTU    0x6
    #define BGEU    0x7

#define LOAD    0x03
    #define LB      0x0
    #define LH      0x1
    #define LW      0x2
    #define LD      0x3
    #define LBU     0x4
    #define LHU     0x5
    #define LWU     0x6

#define STORE   0x23
    #define SB      0x0
    #define SH      0x1
    #define SW      0x2
    #define SD      0x3

#define OP_IMM  0x13
    #define ADDI    0x0
    #define SLLI    0x1
    #define SLTI    0x2
    #define SLTIU   0x3
    #define XORI    0x4
    #define SRI     0x5
        #define SRLI    0x00
        #define SRAI    0x20
    #define ORI     0x6
    #define ANDI    0x7

#define OP      0x33
    #define ADDSUB  0x0
        #define ADD     0x00
        #define SUB     0x20
        #define MUL     0x01
    #define SLL     0x1
    #define SLT     0x2
    #define SLTU    0x3
    #define XOR     0x4
    #define SR      0x5
        #define SRL     0x00
        #define SRA     0x20
        #define DIVU    0x01
    #define OR      0x6
    #define AND     0x7
    #define DIV     0x04  // funct3=0x4, funct7=0x01 for DIV
    #define REM     0x06  // funct3=0x6 for REM
    #define REMU    0x07  // funct3=0x7 for REMU

#define FENCE   0x0f

#define OP_IMM_32 0x1b
    #define ADDIW   0x0
    #define SLLIW   0x1
    #define SRIW    0x5
        #define SRLIW   0x00
        #define SRAIW   0x20

#define OP_32    0x3b
    #define ADDSUB   0x0
        #define ADDW    0x00
        #define MULW    0x01
        #define SUBW    0x20
    #define DIVW    0x4
    #define SLLW    0x1
    #define SRW     0x5
        #define SRLW   0x00
        #define DIVUW   0x01
        #define SRAW   0x20
    #define REMW    0x6
    #define REMUW   0x7

#define SYSTEM  0x73
    #define ECALLBREAK    0x00     // contains both ECALL and EBREAK
    #define CSRRW   0x01
    #define CSRRS   0x02
    #define CSRRC   0x03
    #define CSRRWI  0x05
    #define CSRRSI  0x06
    #define CSRRCI  0x07

#define AMO     0x2f
    #define LR_W        0x02
    #define SC_W        0x03
    #define AMOSWAP_W   0x01
    #define AMOADD_W    0x00
    #define AMOXOR_W    0x04
    #define AMOAND_W    0x0c
    #define AMOOR_W     0x08
    #define AMOMIN_W    0x10
    #define AMOMAX_W    0x14
    #define AMOMINU_W   0x18
    #define AMOMAXU_W   0x1c

//#define AMO_D 0x2f
    //#define LR_D        0x02
    //#define SC_D        0x03
    //#define AMOSWAP_D   0x01
    //#define AMOADD_D    0x00
    //#define AMOXOR_D    0x04
    //#define AMOAND_D    0x0c
    //#define AMOOR_D     0x08
    //#define AMOMIN_D    0x10
    //#define AMOMAX_D    0x14
    //#define AMOMINU_D   0x18
    //#define AMOMAXU_D   0x1c

#endif
