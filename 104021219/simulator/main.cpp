#include "main.hpp"

int main() {
    mem.LoadInstr();
    mem.LoadData();
    for (size_t cycle = 0; cycle < 500000; ++cycle) {
        uint32_t instr = mem.getInstr();
        const char type = IR::getType(instr);
        try {
            if (type == 'R') R_execute(instr);
            else if (type == 'I') I_execute(instr);
            else if (type == 'J') J_execute(instr);
            else if (type == 'S') break;
        } catch (uint32_t ex) {
            // dump error
        }
    }
    return 0;
}

void R_execute(const uint32_t& rhs) {
    const IR::R_type instr = IR::R_decode(rhs);
    const uint32_t funct = instr.funct,
            rs = reg.getReg(instr.rs),
            rt = reg.getReg(instr.rt);
    uint32_t res = 0, err = 0;
    if (funct == 0x08) {
        // jr
        mem.setPC(rs);
    } else if (funct == 0x18) {
        // TODO:mult
    } else if (funct == 0x19) {
        // TODO:multu
    }
    else {
        const uint32_t rd = reg.getReg(instr.rd);
        if (funct == 0x20) {
            // TODO:add
        } else if (funct == 0x21) {
            // addu
            res = rs + rt;
            if (res < rs) err |= ERR_NUMBER_OVERFLOW;
        } else if (funct == 0x22) {
            // TODO:sub
        } else if (funct == 0x24) {
            // and
            res = rs & rt;
        } else if (funct == 0x25) {
            // or
            res = rs | rt;
        } else if (funct == 0x26) {
            // xor
            res = rs ^ rt;
        } else if (funct == 0x27) {
            // nor
            res = ~(rs | rt);
        } else if (funct == 0x28) {
            // nand
            res = ~(rs & rt);
        } else if (funct == 0x2A) {
            // slt
            res = rs < rt ? 1 : 0;
        } else if (funct == 0x00) {
            // sll
            res = rt << instr.shamt;
        } else if (funct == 0x02) {
            // srl
            res = rt >> instr.shamt;
        } else if (funct == 0x03) {
            // TODO:sra
        } else if (funct == 0x10) {
            // TODO:mfhi
        } else if (funct == 0x12) {
            // TODO:mflo
        }
        if (rd == 0) err |= ERR_WRITE_REG_ZERO;
        else reg.setReg(rd, res);
    }
    if (err != 0) throw err;
}

void I_execute(const uint32_t& rhs) {
    const IR::I_type instr = IR::I_decode(rhs);
    const uint32_t opcode = instr.opcode;
    if (opcode == 0x08) {
        // addi
    } else if (opcode == 0x09) {
        // addiu
    } else if (opcode == 0x23) {
        // lw
    } else if (opcode == 0x21) {
        // lh
    } else if (opcode == 0x25) {
        // lhu
    } else if (opcode == 0x20) {
        // lb
    } else if (opcode == 0x24) {
        // lbu
    } else if (opcode == 0x2B) {
        // sw
    } else if (opcode == 0x29) {
        // sh
    } else if (opcode == 0x28) {
        // sb
    } else if (opcode == 0x0F) {
        // lui
    } else if (opcode == 0x0C) {
        // andi
    } else if (opcode == 0x0D) {
        // ori
    } else if (opcode == 0x0E) {
        // nori
    } else if (opcode == 0x0A) {
        // slti
    } else if (opcode == 0x04) {
        // beq
    } else if (opcode == 0x05) {
        // bne
    } else if (opcode == 0x07) {
        // bgtz
    }
}

void J_execute(const uint32_t& rhs) {
    const IR::J_type instr = IR::J_decode(rhs);
    const uint32_t opcode = instr.opcode;
    if (opcode == 0x02) {
        // j
    } else if (opcode == 0x03) {
        // jal
    }
}
