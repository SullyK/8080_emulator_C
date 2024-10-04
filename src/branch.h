#ifndef BRANCH_FUNCS
#define BRANCH_FUNCS
#include "cpu.h"
#include "flags.h"
#include "helpers.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
// insert functions here
void jmp_addr(CPU *cpu, int high_byte, int low_byte);
//continue from here, don't forget to implement the functions for the data-transfer group
#ifdef __cplusplus
}
#endif

#endif
