#ifndef REGFILE_DEF
#define REGFILE_DEF
class regfile {
public:
    regfile() {}
    regfile(const regfile& rhs) {
        for (size_t i = 0; i < 32; ++i) {
            reg_[i] = rhs.getReg(i);
        }
    }
    const uint32_t& getReg(const size_t& idx) const { return reg_[idx]; }
    void setReg(const size_t& idx, const uint32_t& rhs) {
        if (idx != 0) reg_[idx] = rhs;
    }

private:
    uint32_t reg_[32] = {};
};
#endif
