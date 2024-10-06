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
void conditional_jump(CPU *cpu, int high_byte, int low_byte, condition);
void call_addr(CPU *cpu, int high_byte, int low_byte);
void conditional_call(CPU *cpu, int high_byte, int low_byte);
void branch_return(CPU *cpu);
void conditional_branch_return(CPU *cpu, uint8_t condition);

// NZ - not zero (Z = 0)  - 0
// Z - zero (Z = 1) - 1
// NC - no carry (CY = 0) - 2
// C - carry (CY = 1) - 3
// PO - parity odd (P = 0) - 4
// PE - parity even (P = 1) - 5
// P - plus (S = 0) - 6
// M -minus(S=1) - 7
#ifdef __cplusplus
}
#endif

#endif
