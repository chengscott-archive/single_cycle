#ifndef IRFILE_DEF
#define IRFILE_DEF
#include <cstdint>

namespace IR {
    struct IR_type {};

    struct R_type : IR_type {
    	uint32_t opcode, rs, rt, rd, shamt, funct;
    };

    struct I_type : IR_type {
    	uint32_t opcode, rs, rt, C;
    };

    struct J_type : IR_type {
    	uint32_t opcode, C;
    };

    struct S_type : IR_type {
    	uint32_t opcode, C;
    };

    char getType(const uint32_t&);
    // decode
    R_type R_decode(const uint32_t&);
    I_type I_decode(const uint32_t&);
    J_type J_decode(const uint32_t&);
    S_type S_decode(const uint32_t&);
    // execute
    void R_execute(const uint32_t&);
    void I_execute(const uint32_t&);
    void J_execute(const uint32_t&);
}
#endif
