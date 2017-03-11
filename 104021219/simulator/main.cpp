#include <iostream>
#include "memory.hpp"
#include "regfile.hpp"
#include "irfile.hpp"

int main() {
    memory mem;
    mem.LoadInstr();
    mem.LoadData();
    for (size_t cycle = 0; cycle < 500000; ++cycle) {
        uint32_t instr = mem.getInstr();
        const char type = IR::getType(instr);
        if (type == 'R') IR::R_execute(instr);
        else if (type == 'I') IR::I_execute(instr);
        else if (type == 'J') IR::J_execute(instr);
        else if (type == 'S') break;
    }
    return 0;
}
