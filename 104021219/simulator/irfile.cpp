#include "irfile.hpp"

void IR::decode(const uint32_t& rhs) {
    uint32_t opcode = (rhs >> 26) & 0x3f;
    switch (opcode) {
        case 0x0:
            type_ = 'R';
            R_decode(rhs);
            break;
        case 0x2:
        case 0x3:
            type_ = 'J';
            J_decode(rhs);
            break;
        case 0x3f:
            type_ = 'S';
            S_decode(rhs);
            break;
        default:
            type_ = 'I';
            I_decode(rhs);
            break;
    }
}

void IR::R_decode(const uint32_t& rhs) {
    R_type res;
    res.opcode = (rhs >> 26) & 0x3f;
    res.rs = (rhs >> 21) & 0x1f;
	res.rt = (rhs >> 16) & 0x1f;
	res.rd = (rhs >> 11) & 0x1f;
	res.shamt = (rhs >> 6) & 0x1f;
	res.funct = rhs & 0x3f;
    instr_ = res;
}

void IR::I_decode(const uint32_t& rhs) {
    I_type res;
    res.opcode = (rhs >> 26) & 0x3f;
	res.rs = (rhs >> 21) & 0x1f;
	res.rt = (rhs >> 16) & 0x1f;
	res.C = rhs & 0xffff;
    instr_ = res;
}

void IR::J_decode(const uint32_t& rhs) {
    J_type res;
    res.opcode = (rhs >> 26) & 0x3f;
	res.C = rhs & 0x3ffffff;
    instr_ = res;
}

void IR::S_decode(const uint32_t& rhs) {
    S_type res;
    res.opcode = (rhs >> 26) & 0x3f;
	res.C = rhs & 0x3ffffff;
    instr_ = res;
}
