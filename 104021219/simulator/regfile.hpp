#ifndef REGFILE_DEF
#define REGFILE_DEF
class regfile {
public:
    regfile() {}
    regfile(const regfile& rhs) {
        for (size_t i = 0; i < 32; ++i) {
            reg_[i] = rhs.getReg(i);
        }
        HI_ = rhs.getHI();
        LO_ = rhs.getLO();
    }
    const uint32_t& getReg(const size_t& idx) const { return reg_[idx]; }
    void setReg(const size_t& idx, const uint32_t& rhs) {
        if (idx != 0) reg_[idx] = rhs;
    }
    const uint32_t& getHI() const { return HI_; }
    void setHI(const uint32_t& rhs) { HI_ = rhs; }
    const uint32_t& getLO() const { return LO_; }
    void setLO(const uint32_t& rhs) { LO_ = rhs; }

private:
    uint32_t reg_[32] = {}, HI_ = 0, LO_ = 0;
};
#endif
