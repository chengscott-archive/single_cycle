#ifndef REGFILE_DEF
#define REGFILE_DEF
class regfile {
public:
    const uint32_t& getReg(const size_t& idx) const { return reg_[idx]; }
    void setReg(const size_t& idx, const uint32_t& val) {
        if (idx == 0) throw "Write $0 Error";
        reg_[idx] = val;
    }

private:
    uint32_t reg_[32] = {};
};
#endif
