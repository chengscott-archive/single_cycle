#ifndef MEMORY_DEF
#define MEMORY_DEF
#include <fstream>
#include <queue>
using namespace std;
#define ToBig(x) (__builtin_bswap32(x))

class memory {
public:
    void load();
    const uint32_t& getPC() const { return PC_; }
    const uint32_t& getCount() const { return icount_; }
    const uint32_t getInstr();

private:
    uint32_t PC_ = 0, icount_ = 0;
    queue<uint32_t> instr_;
};
#endif
