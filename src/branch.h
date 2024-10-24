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
void jmp_addr(CPU *cpu, int high_byte, int low_byte); // JMP addr
void conditional_jump(CPU *cpu, int high_byte, int low_byte, uint8_t condition); // Jcondition addr
void call_addr(CPU *cpu, int high_byte, int low_byte); // CALL addr
//@@@!!!TODO: MAJOR PAIN-POINT IN MAIN - Will constantly need to check these
//functions so I need to ensure these are conistent so I don't mess up later.
void conditional_call(CPU *cpu, int high_byte, int low_byte, uint8_t condition); // Cconditional addr
void branch_return(CPU *cpu); // RET
void conditional_branch_return(CPU *cpu, uint8_t condition); //Rcondition
void restart(CPU *cpu, uint8_t n_value); //RST n
void PCHL(CPU *cpu); //PCHL

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
