#include <iostream>
#include "memory.hpp"
using namespace std;

int main() {
    memory mem;
    mem.LoadInstr();
    mem.LoadData();
    cout << mem.getPC() << endl;
    uint32_t c = mem.getICount();
    for (int i = 0; i < c; ++i) cout << mem.getInstr() << endl;
    cout << endl << mem.getSP() << endl;
    uint32_t d = mem.getDCount();
    for (int i = 0; i < d; ++i) cout << mem.getData(i) << endl;
    return 0;
}
