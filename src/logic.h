#ifndef LOGIC_FUNCS
#define LOGIC_FUNCS
#include "flags.h"
#include "cpu.h"
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
void and_register(CPU *cpu, uint8_t reg);
void and_memory(CPU *cpu, uint16_t HL);
void and_immediate(CPU *cpu, uint8_t byte);
void exclusive_or_register(CPU *cpu, uint8_t reg);
void exclusive_or_memory(CPU *cpu, uint16_t HL);
void exclusive_or_immediate(CPU *cpu, uint8_t byte);
#ifdef __cplusplus
}
#endif

#endif

