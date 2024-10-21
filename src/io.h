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

void push_rp(CPU *cpu, uint16_t rp);
void push_psw(CPU *cpu);
void pop_rp(CPU *cpu, uint16_t *rp);
void pop_psw(CPU *cpu);
void XTHL(CPU *cpu);
void SPHL(CPU *cpu);
void EI(CPU *cpu);
void DI(CPU *cpu);
void HTL();
void NOP();
#ifdef __cplusplus
}
#endif

#endif
