#ifndef IO_FUNCS
#define IO_FUNCS

#include "cpu.h"
#include "helpers.h"
#include <stdio.h>

// prevent name-mangling in C++ testing
#ifdef __cplusplus
extern "C" {
#endif

void push_rp(CPU *cpu, uint16_t rp);
void push_psw(CPU *cpu);
void pop_rp(CPU *cpu, uint16_t *rp);
void pop_psw(CPU *cpu);
#ifdef __cplusplus
}
#endif

#endif
