#include "irfile.hpp"

char IR::getType(const uint32_t& rhs) {
    uint32_t opcode = (rhs >> 26) & 0x3f;
    if (opcode == 0x0) return 'R';
    else if (opcode == 0x2 || opcode == 0x3) return 'J';
    else if (opcode == 0x3f) return 'S';
    return 'I';
}

IR::R_type IR::R_decode(const uint32_t& rhs) {
    R_type res;
    res.opcode = (rhs >> 26) & 0x3f;
    res.rs = (rhs >> 21) & 0x1f;
    res.rt = (rhs >> 16) & 0x1f;
    res.rd = (rhs >> 11) & 0x1f;
    res.shamt = (rhs >> 6) & 0x1f;
    res.funct = rhs & 0x3f;
    return res;
}

IR::I_type IR::I_decode(const uint32_t& rhs) {
    I_type res;
    res.opcode = (rhs >> 26) & 0x3f;
    res.rs = (rhs >> 21) & 0x1f;
    res.rt = (rhs >> 16) & 0x1f;
    res.C = rhs & 0xffff;
    return res;
}

IR::J_type IR::J_decode(const uint32_t& rhs) {
    J_type res;
    res.opcode = (rhs >> 26) & 0x3f;
    res.C = rhs & 0x3ffffff;
    return res;
}

IR::S_type IR::S_decode(const uint32_t& rhs) {
    S_type res;
    res.opcode = (rhs >> 26) & 0x3f;
    res.C = rhs & 0x3ffffff;
    return res;
}

void IR::R_execute(const uint32_t& rhs) {
    const R_type instr = R_decode(rhs);
    if (instr.funct == 0x20) ;
}

void IR::I_execute(const uint32_t& rhs) {

}

void IR::J_execute(const uint32_t& rhs) {

}
