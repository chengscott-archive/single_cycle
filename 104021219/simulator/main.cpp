#include <iostream>
#include "memory.hpp"
using namespace std;

int main() {
    memory mem;
    mem.load();
    cout << mem.getPC() << endl;
    uint32_t c = mem.getCount();
    for (int i = 0; i < c; ++i) cout << mem.getInstr() << endl;
    return 0;
}
