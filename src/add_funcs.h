#ifndef ADD_FUNCS
#define ADD_FUNCS
#include "art.h"
#include "cpu.h"
#include "helpers.h"
#include <stdint.h>
                              
#ifdef __cplusplus
extern "C" {
#endif

void add_register(CPU *cpu, uint8_t reg_value);
void add_data(CPU *cpu, uint8_t byte_two);
void add_memory(CPU *cpu, uint16_t HL);
void add_register_carry(CPU *cpu, uint8_t register_value);
void add_memory_carry(CPU *cpu, uint16_t HL);
void add_data_carry(CPU *cpu, uint8_t byte_two);
void subtract_register(CPU *cpu, uint8_t reg_value);
void subtract_register_carry(CPU *cpu, uint8_t register_value);
void subtract_data(CPU *cpu, uint8_t byte_two);
void subtract_data_carry(CPU *cpu, uint8_t byte_two);
void subtract_memory(CPU *cpu, uint16_t HL);
void subtract_memory_carry(CPU *cpu, uint16_t HL);
void increment_register(CPU *cpu, uint8_t *reg);
void increment_memory(CPU *cpu, uint16_t HL);
void decrement_register(CPU *cpu, uint8_t *reg);
void decrement_memory(CPU *cpu, uint16_t HL);
void increment_register_pair(uint8_t *high,uint8_t *low);
void decrement_register_pair(uint8_t *high, uint8_t *low);
void add_reg_pair_to_HL(CPU *cpu, uint8_t *high, uint8_t *low);
void decimal_adjust_accumulator(CPU *cpu);
#ifdef __cplusplus
}
#endif

#endif
