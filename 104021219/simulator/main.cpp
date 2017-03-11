#include <iostream>
#include "memory.hpp"
#include "irfile.hpp"
using namespace std;

int main() {
    memory mem;
    mem.LoadInstr();
    mem.LoadData();
    for (uint32_t cycle = 0; cycle < 500000; ++cycle) {
        uint32_t instr = mem.getInstr();
        IR ir(instr);
        cout << instr << endl;
        cout << ir.getType() << endl;
        if (ir.getType() == 'S') break;
    }

    return 0;
}
