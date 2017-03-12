#include <iostream>
#include "memory.hpp"
#include "regfile.hpp"
#include "irfile.hpp"
#define ERR_WRITE_REG_ZERO 0x1
#define ERR_NUMBER_OVERFLOW 0x10
#define ERR_OVERWRTIE_REG_HI_LO 0x100
#define ERR_ADDRESS_OVERFLOW 0x1000
#define ERR_MISALIGNMENT 0x10000

memory mem;
regfile reg;

void R_execute(const uint32_t&);
void I_execute(const uint32_t&);
void J_execute(const uint32_t&);
