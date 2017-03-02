#include "memory.hpp"

void memory::LoadInstr() {
    ifstream image("iimage.bin", ios::in | ios::binary);
    int v;
    image.read((char *) &v, sizeof(int));
    PC_ = ToBig(v);
    image.read((char *) &v, sizeof(int));
    icount_ = ToBig(v);
    for (uint32_t i = 0; i < icount_; ++i) {
        image.read((char *) &v, sizeof(int));
        instr_.push(ToBig(v));
    }
    image.close(); 
}

void memory::LoadData() {
    ifstream image("dimage.bin", ios::in | ios::binary);
    int v;
    image.read((char *) &v, sizeof(int));
    SP_ = ToBig(v);
    image.read((char *) &v, sizeof(int));
    dcount_ = ToBig(v);
    for (uint32_t i = 0; i < dcount_; ++i) {
        image.read((char *) &v, sizeof(int));
        data_[i] = ToBig(v);
    }
    image.close(); 
}

const uint32_t memory::getInstr() {
    PC_++;
    const uint32_t ret = instr_.front();
    instr_.pop();
    return ret; 
}

