#ifndef ADD_FUNCS
#define ADD_FUNCS
#include <stdint.h>
#include "art.h"
#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

void add_register(CPU *cpu, uint8_t reg_value);

#ifdef __cplusplus
}
#endif

#endif

