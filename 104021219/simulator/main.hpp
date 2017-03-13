#include <cstdio>
#include "memory.hpp"
#include "regfile.hpp"
#include "irfile.hpp"
// ERR constant
#define ERR_WRITE_REG_ZERO 0x1 // continue
#define ERR_NUMBER_OVERFLOW 0x10  // continue
#define ERR_OVERWRTIE_REG_HI_LO 0x100 // continue
#define ERR_ADDRESS_OVERFLOW 0x1000 //halt
#define ERR_MISALIGNMENT 0x10000 //halt
// 16-bit C sign extend to 32-bit
#define SignExt16(C) (((C) >> 15 == 0x0) ? ((C) & 0x0000ffff) : ((C) | 0xffff0000))
// 8-bit C sign extend to 32-bit
#define SignExt8(C) (((C) >> 7 == 0x0) ? ((C) & 0x000000ff) : ((C) | 0xffffff00))
// 16-bit C zero extend to 32-bit
#define ZeroExt16(C) ((C) & 0x0000ffff)
// check if a+b overflows
#define isOverflow(a, b) (((((a) >> 31)^((b) >> 31)) == 0) && ((((a) >> 31)^(((a) + (b)) >> 31)) == 1) ? ERR_NUMBER_OVERFLOW : 0)
// {14'{C[15]}, C, 2'b0}
#define BranchAddr(C) ((C) >> 15 == 0x0 ? (0x0003ffff & ((C) << 2)) : (0xfffc0000 | ((C) << 2)))

memory mem;
regfile reg;

void R_execute(const uint32_t);
void I_execute(const uint32_t);
void J_execute(const uint32_t);
