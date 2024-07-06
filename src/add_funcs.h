#ifndef ADD_FUNCS
#define ADD_FUNCS
#include "art.h"
#include "cpu.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void add_register(CPU *cpu, uint8_t reg_value);
void add_memory(CPU *cpu, uint16_t HL);

#ifdef __cplusplus
}
#endif

#endif
