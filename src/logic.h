#ifndef LOGIC_FUNCS
#define LOGIC_FUNCS
#include "flags.h"
#include "cpu.h"
#include "helpers.h"
#include <stdint.h>
                              
#ifdef __cplusplus
extern "C" {
#endif

// place funcs here
void and_register(CPU *cpu, uint8_t reg);
#ifdef __cplusplus
}
#endif

#endif

