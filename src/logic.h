#ifndef LOGIC_FUNCS
#define LOGIC_FUNCS
#include "cpu.h"
#include "flags.h"
#include "helpers.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// @@@ TODO: register/immediates are sometimes
// literally the same in terms of implementation
// I will still test independently because I may just
// pass the actual register, not the value only
// I have yet to decide, I might do it when I get to
// the main loop
void and_register(CPU *cpu, uint8_t reg); //ANA r
void and_memory(CPU *cpu, uint16_t HL); // ANA M
void and_immediate(CPU *cpu, uint8_t byte); //ANI data
void exclusive_or_register(CPU *cpu, uint8_t reg);//XRA r
void exclusive_or_memory(CPU *cpu, uint16_t HL); //XRA m
void exclusive_or_immediate(CPU *cpu, uint8_t byte); //XRI data
void or_register(CPU *cpu, uint8_t reg); // ORA r
void or_memory(CPU *cpu, uint16_t HL);  // ORA m
void or_immediate(CPU *cpu, uint8_t reg); // ORI data
void compare_register(CPU *cpu, uint8_t reg); // CMP r
void compare_memory(CPU *cpu, uint16_t reg); //CMP M
void compare_immediate(CPU *cpu, uint8_t byte_two); //CPI data
void rotate_left(CPU *cpu); //RLC
void rotate_right(CPU *cpu); //RRC
void rotate_left_carry(CPU *cpu); //RAL
void rotate_right_carry(CPU *cpu); //RAR
void complement_accumulator(CPU *cpu); //CMA
void complement_carry(CPU *cpu); //CMC
void set_carry(CPU *cpu); // STC
#ifdef __cplusplus
}
#endif

#endif
