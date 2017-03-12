#include <iostream>
#include "memory.hpp"
#include "regfile.hpp"
#include "irfile.hpp"

memory mem;
regfile reg;

void R_execute(const uint32_t&);
void I_execute(const uint32_t&);
void J_execute(const uint32_t&);
