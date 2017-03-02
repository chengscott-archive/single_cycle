#ifndef MEMORY_DEF
#define MEMORY_DEF
#include <fstream>
#include <queue>
using namespace std;
#define ToBig(x) (__builtin_bswap32(x))

class memory {
public:
    void LoadInstr();
    void LoadData();
    const uint32_t& getPC() const { return PC_; }
    const uint32_t& getSP() const { return SP_; }
    const uint32_t& getICount() const { return icount_; }
    const uint32_t& getDCount() const { return dcount_; }
    const uint32_t getInstr();
    const uint32_t& getData(const uint32_t& rhs) const {
        return data_[rhs];
    }

private:
    uint32_t PC_ = 0, SP_ = 0, icount_ = 0, dcount_ = 0;
    queue<uint32_t> instr_;
    uint32_t data_[1024];
};
#endif
