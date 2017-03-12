#ifndef MEMORY_DEF
#define MEMORY_DEF
#include <fstream>
#include <vector>
using namespace std;
#define ToBig(x) (__builtin_bswap32(x))

class memory {
public:
    void LoadInstr();
    void LoadData();
    const uint32_t& getPC() const { return PC_; }
    void setPC(const uint32_t& rhs) { PC_ = rhs; }
    const uint32_t& getSP() const { return SP_; }
    const size_t& getICount() const { return icount_; }
    const size_t& getDCount() const { return dcount_; }
    const uint32_t getInstr();
    const uint32_t& getData(const size_t& rhs) const {
        return data_[rhs];
    }

private:
    uint32_t PC_ = 0, PC0_ = 0, SP_ = 0;
    size_t icount_ = 0, dcount_ = 0;
    vector<uint32_t> instr_;
    uint32_t data_[1024];
};
#endif
