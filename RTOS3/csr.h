#ifndef CSR
#define CSR


#include <types.h>

uint64 r_mstatus();

void w_mstatus(uint64 x);

uint64 r_mie();

void w_mie(uint64 x);

void w_mtvec(uint64 x);

void w_stimecmp(uint64 x);

uint64 r_time();


#endif