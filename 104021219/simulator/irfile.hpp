#ifndef IRFILE_DEF
#define IRFILE_DEF
#include <cstdint>

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

class IR {
public:
    IR() { }
    IR(const uint32_t& rhs) {
        decode(rhs);
    }
    const char& getType() const {
        return type_;
    }

private:
    void decode(const uint32_t& rhs);
    void R_decode(const uint32_t& rhs);
    void I_decode(const uint32_t& rhs);
    void J_decode(const uint32_t& rhs);
    void S_decode(const uint32_t& rhs);
    char type_;
    IR_type instr_;
};
#endif
