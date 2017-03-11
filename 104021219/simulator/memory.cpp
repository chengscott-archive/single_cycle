#include "memory.hpp"

void memory::LoadInstr() {
    ifstream image("iimage.bin", ios::in | ios::binary);
    int v;
    image.read((char *) &v, sizeof(int));
    PC_ = PC0_ = ToBig(v);
    image.read((char *) &v, sizeof(int));
    icount_ = ToBig(v);
    for (size_t i = 0; i < icount_; ++i) {
        image.read((char *) &v, sizeof(int));
        // TODO: stop when read halt
        instr_.push_back(ToBig(v));
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
    for (size_t i = 0; i < dcount_; ++i) {
        image.read((char *) &v, sizeof(int));
        data_[i] = ToBig(v);
    }
    image.close(); 
}

const uint32_t memory::getInstr() {
    const uint32_t ret = instr_[(PC_ - PC0_) / 4];
    PC_ += 4;
    return ret; 
}

