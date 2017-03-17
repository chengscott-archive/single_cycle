#include "main.hpp"

int main() {
    snapshot = fopen("snapshot.rpt", "w");
    error_dump = fopen("error_dump.rpt", "w");
    mem.LoadInstr();
    uint32_t SP = mem.LoadData();
    reg.setReg(29, SP);
    dump_reg(0);
    for (size_t cycle = 1; cycle <= 500000; ++cycle) {
        uint32_t instr = mem.getInstr();
        const char type = IR::getType(instr);
        try {
            if (type == 'R') R_execute(instr);
            else if (type == 'I') I_execute(instr);
            else if (type == 'J') J_execute(instr);
            else if (type == 'S') break;
            else {
                printf("illegal instruction found at 0x%08X\n", mem.getPC());
                break;
            }
        } catch (uint32_t ex) {
            // dump error
            if (ex & ERR_WRITE_REG_ZERO) {
                fprintf(error_dump, "In cycle %zu: Write $0 Error\n", cycle);
            }
            if (ex & ERR_NUMBER_OVERFLOW) {
                fprintf(error_dump, "In cycle %zu: Number Overflow\n", cycle);
            }
            if (ex & ERR_OVERWRTIE_REG_HI_LO) {
                fprintf(error_dump,
                        "In cycle %zu: Overwrite HI-LO registers\n",
                        cycle);
            }
            if (ex & ERR_ADDRESS_OVERFLOW) {
                fprintf(error_dump, "In cycle %zu: Address Overflow\n", cycle);
                break;
            }
            if (ex & ERR_MISALIGNMENT) {
                fprintf(error_dump, "In cycle %zu: Misalignment Error\n", cycle);
                break;
            }
        }
        dump_reg(cycle);
    }
    fclose(snapshot);
    fclose(error_dump);
    return 0;
}

void dump_reg(const size_t cycle) {
    fprintf(snapshot, "cycle %zu\n", cycle);
    for (int i = 0; i < 32; ++i) {
        if (cycle == 0 || reg.getReg(i) != regt.getReg(i))
            fprintf(snapshot, "$%02d: 0x%08X\n", i, reg.getReg(i));
    }
    if (cycle == 0 || reg.getHI() != regt.getHI())
        fprintf(snapshot, "$HI: 0x%08X\n", reg.getHI());
    if (cycle == 0 || reg.getLO() != regt.getLO())
        fprintf(snapshot, "$LO: 0x%08X\n", reg.getLO());
    fprintf(snapshot, "PC: 0x%08X\n\n\n", mem.getPC());
    regt = reg;
}

void R_execute(const uint32_t rhs) {
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
        uint64_t m = rs * rt;
        // err |= isOverflow(rs, rt);
        bool isOverwrite = reg.setHILO(m >> 32, m & 0x00000000ffffffff);
        err |= (isOverwrite ? ERR_OVERWRTIE_REG_HI_LO : 0);
    } else if (funct == 0x19) {
        // multu
        uint64_t m = (uint64_t) rs * (uint64_t) rt;
        bool isOverwrite = reg.setHILO(m >> 32, m & 0x00000000ffffffff);
        err |= (isOverwrite ? ERR_OVERWRTIE_REG_HI_LO : 0);
    } else if (funct == 0x00) {
        // sll
        if (instr.rd == 0 && !(rt == 0 && instr.shamt == 0))
            err |= ERR_WRITE_REG_ZERO;
        else reg.setReg(instr.rd, rt << instr.shamt);
    } else {
        if (funct == 0x20) {
            // add
            res = rs + rt;
            err |= isOverflow(rs, rt);
        } else if (funct == 0x21) {
            // addu
            res = rs + rt;
        } else if (funct == 0x22) {
            // sub
            const uint32_t nrt = ~rt + 1;
            res = rs + nrt;
            err |= (nrt == 0x80000000 ? ERR_NUMBER_OVERFLOW : 0);
            err |= isOverflow(rs, nrt);
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
        } else if (funct == 0x02) {
            // srl
            res = rt >> instr.shamt;
        } else if (funct == 0x03) {
            // TODO:sra
        } else if (funct == 0x10) {
            // mfhi
            res = reg.fetchHI();
        } else if (funct == 0x12) {
            // mflo
            res = reg.fetchLO();
        }
        if (instr.rd == 0) err |= ERR_WRITE_REG_ZERO;
        else reg.setReg(instr.rd, res);
    }
    if (err != 0) throw err;
}

void I_execute(const uint32_t rhs) {
    const IR::I_type instr = IR::I_decode(rhs);
    const uint32_t opcode = instr.opcode,
            rs = reg.getReg(instr.rs),
            rt = reg.getReg(instr.rt),
            C = instr.C;
    uint32_t res = 0, err = 0;
    if (opcode == 0x04 || opcode == 0x05 || opcode == 0x07) {
        // beq, bne, bgtz
        const uint32_t Caddr = BranchAddr(C);
        res = mem.getPC() + Caddr;
        err |= isOverflow(mem.getPC(), Caddr);
        if ((opcode == 0x04 && rs == rt) ||
                (opcode == 0x05 && rs != rt) ||
                (opcode == 0x07 && rs > 0))
            mem.setPC(res);
    } else {
        if (instr.rt == 0) err |= ERR_WRITE_REG_ZERO;
        if (opcode == 0x08) {
            // addi
            const uint32_t Cext = SignExt16(C);
            res = rs + Cext;
            err |= isOverflow(rs, Cext);
            reg.setReg(instr.rt, res);
        } else if (opcode == 0x09) {
            // addiu
            reg.setReg(instr.rt, rs + SignExt16(C));
        } else if (opcode == 0x0F) {
            // lui
            reg.setReg(instr.rt, C << 16);
        } else if (opcode == 0x0C) {
            // andi
            reg.setReg(instr.rt, rs & ZeroExt16(C));
        } else if (opcode == 0x0D) {
            // ori
            reg.setReg(instr.rt, rs | ZeroExt16(C));
        } else if (opcode == 0x0E) {
            // nori
            reg.setReg(instr.rt, ~(rs | ZeroExt16(C)));
        } else if (opcode == 0x0A) {
            // slti
            reg.setReg(instr.rt, rs < ZeroExt16(C) ? 1 : 0);
        }  else {
            const uint32_t Cext = SignExt16(C);
            res = rs + Cext;
            err |= isOverflow(rs, Cext);
            if (res >= 1024) throw (err | ERR_ADDRESS_OVERFLOW);
            if (opcode == 0x23) {
                // lw
                if (res % 4 != 0) throw (err | ERR_MISALIGNMENT);
                reg.setReg(instr.rt, mem.loadWord(res));
            } else if (opcode == 0x21) {
                // lh
                if (res % 2 != 0) throw (err | ERR_MISALIGNMENT);
                reg.setReg(instr.rt, SignExt16(mem.loadHalfWord(res)));
            } else if (opcode == 0x25) {
                // lhu
                if (res % 2 != 0) throw (err | ERR_MISALIGNMENT);
                reg.setReg(instr.rt, mem.loadHalfWord(res) & 0xffff);
            } else if (opcode == 0x20) {
                // lb
                reg.setReg(instr.rt, SignExt8(mem.loadByte(res)));
            } else if (opcode == 0x24) {
                // lbu
                reg.setReg(instr.rt, mem.loadByte(res) & 0xff);
            } else if (opcode == 0x2B) {
                // sw
                if (res % 4 != 0) throw (err | ERR_MISALIGNMENT);
                mem.saveWord(res, rt);
            } else if (opcode == 0x29) {
                // sh
                if (res % 2 != 0) throw (err | ERR_MISALIGNMENT);
                mem.saveHalfWord(res, rt);
            } else if (opcode == 0x28) {
                // sb
                mem.saveByte(res, rt);
            }
        }
    }
    if (err != 0) throw err;
}

void J_execute(const uint32_t rhs) {
    const IR::J_type instr = IR::J_decode(rhs);
    if (instr.opcode == 0x03) {
        // jal
        reg.setReg(31, mem.getPC());
    }
    // j && jal: PC = {(PC+4)[31:28], C, 2'b0}
    mem.setPC((mem.getPC() & 0xf0000000) | (instr.C << 2));
}
