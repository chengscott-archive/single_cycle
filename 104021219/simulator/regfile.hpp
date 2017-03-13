#ifndef REGFILE_DEF
#define REGFILE_DEF
#include <cstdint>
#include <cstdio>
class regfile {
public:
    const uint32_t& getReg(const size_t& idx) const { return reg_[idx]; }
    void setReg(const size_t& idx, const uint32_t& rhs) {
        if (idx != 0) reg_[idx] = rhs;
    }
    void dump() const;

private:
    uint32_t reg_[32] = {};
};
#endif
