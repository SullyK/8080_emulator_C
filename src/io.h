#ifndef IO_FUNCS
#define IO_FUNCS

#include "cpu.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// prevent name-mangling in C++ testing
#ifdef __cplusplus
extern "C" {
#endif

void push_rp(CPU *cpu, uint16_t rp); // PUSH rp
void push_psw(CPU *cpu); // PUSH PSW
void pop_rp(CPU *cpu, uint16_t *rp); // POP rp
void pop_psw(CPU *cpu); // POP PSW
void XTHL(CPU *cpu); //XTHL
void SPHL(CPU *cpu); //SPHL
void EI(CPU *cpu); //EI
void DI(CPU *cpu); //DI
void HTL(void); //HLT
void NOP(void); //NOP
//@@@!!!TODO: add ports in and out prototypes
#ifdef __cplusplus
}
#endif

#endif
