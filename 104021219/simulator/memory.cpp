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

uint32_t memory::LoadData() {
    ifstream image("dimage.bin", ios::in | ios::binary);
    int v;
    image.read((char *) &v, sizeof(int));
    uint32_t SP = ToBig(v);
    image.read((char *) &v, sizeof(int));
    dcount_ = ToBig(v);
    for (size_t i = 0; i < dcount_; ++i) {
        image.read((char *) &v, sizeof(int));
        data_[i] = ToBig(v);
    }
    image.close();
    return SP;
}

const uint32_t memory::getInstr() {
    const uint32_t ret = instr_[(PC_ - PC0_) / 4];
    PC_ += 4;
    return ret;
}

const uint32_t memory::loadWord(const size_t rhs) const {
    return data_[rhs] |
            data_[rhs + 1] << 8 |
            data_[rhs + 2] << 16 |
            data_[rhs + 3] << 24;
}
const uint32_t memory::loadHalfWord(const size_t rhs) const {
    return data_[rhs] | data_[rhs + 1] << 8;
}
const uint32_t memory::loadByte(const size_t rhs) const {
    return data_[rhs];
}

void memory::saveWord(const size_t lhs, const uint32_t rhs) {
    data_[lhs] = rhs & 0xff;
	data_[lhs + 1] = (rhs >> 8) & 0xff;
	data_[lhs + 2] = (rhs >> 16) & 0xff;
	data_[lhs + 3] = (rhs >> 24) & 0xff;
}

void memory::saveHalfWord(const size_t lhs, const uint32_t rhs) {
    data_[lhs] = rhs & 0xff;
	data_[lhs + 1] = (rhs >> 8) & 0xff;
}

void memory::saveByte(const size_t lhs, const uint32_t rhs) {
    data_[lhs] = rhs;
}
