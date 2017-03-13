#include "regfile.hpp"

void regfile::dump() const {
    for (int i = 0; i < 32; ++i) {
        printf("$%02d: 0x%08x\n", i, reg_[i]);
    }
}
