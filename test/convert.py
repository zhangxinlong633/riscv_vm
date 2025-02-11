import sys
import struct

# RISC-V 指令 OpCode 和 funct3/7 的定义
OPCODES = {
    'addi': 0b0010011,
    'add':  0b0110011,
    'sub':  0b0110011,
    'mul':  0b0110011,
    'div':  0b0110011
}

FUNCT3 = {
    'addi': 0b000,
    'add':  0b000,
    'sub':  0b000,
    'mul':  0b000,
    'div':  0b100
}

FUNCT7 = {
    'add':  0b0000000,
    'sub':  0b0100000,
    'mul':  0b0000001,
    'div':  0b0000001
}

# 立即数指令格式生成
def generate_addi(rd, rs1, imm):
    opcode = OPCODES['addi']
    funct3 = FUNCT3['addi']
    imm &= 0xfff  # 12-bit immediate
    return (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode

# R型指令格式生成
def generate_rtype(op, rd, rs1, rs2):
    opcode = OPCODES[op]
    funct3 = FUNCT3[op]
    funct7 = FUNCT7[op]
    return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode

def main():
    if len(sys.argv) != 5:
        print("Usage: python3 convert.py <operation> <operand1> <operand2> <output_file>")
        return

    operation = sys.argv[1]
    operand1 = int(sys.argv[2])
    operand2 = int(sys.argv[3])
    output_file = sys.argv[4]

    # 暂时硬编码寄存器号，通常做测试或原型开发用
    rd = 10  # 使用寄存器 a0
    rs1 = 10 # 使用寄存器 a0
    rs2 = 11 # 使用寄存器 a1

    # 假设 operand1 和 operand2 已经在寄存器 a0 和 a1 中
    if operation == 'addi':
        instruction = generate_addi(rd, rs1, operand2)
    elif operation in ['add', 'sub', 'mul', 'div']:
        instruction = generate_rtype(operation, rd, rs1, rs2)
    else:
        print("Unsupported operation.")
        return

    # 将指令写入指定的二进制文件
    with open(output_file, "wb") as f:
        f.write(struct.pack("<I", instruction))
    
    print(f"Binary file '{output_file}' generated successfully for operation {operation}.")

if __name__ == "__main__":
    main()

