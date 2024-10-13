#ifndef DATA_FUNCS
#define DATA_FUNCS
#include "cpu.h"
#include "flags.h"
#include "helpers.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
// insert functions here
void move_register(uint8_t *src, uint8_t *dest);
void move_from_memory(CPU *cpu, uint16_t src, uint8_t *dest);
void move_to_memory(CPU *cpu, uint8_t *src, uint16_t dest);
void move_immediate(uint8_t src, uint8_t *dest);
void move_immediate_to_memory(CPU *cpu, uint8_t src, uint16_t dest);
void load_reg_pair_immed(uint8_t reg_high, uint8_t low,
                         uint16_t *register_pair);
void load_acc_direct(CPU *cpu, uint8_t reg_high, uint8_t reg_low);
void load_h_l_direct(CPU *cpu, uint8_t reg_high, uint8_t reg_low);
void store_acc_direct(CPU *cpu, uint8_t high_byte, uint8_t low_byte);
void store_h_l_direct(CPU *cpu, uint8_t reg_high, uint8_t reg_low);
void load_acc_indirect(CPU *cpu, uint16_t register_pair);
void store_acc_indirect(CPU *cpu, uint16_t register_pair);
void exchange_hl_with_de(CPU *cpu);

#ifdef __cplusplus
}
#endif

#endif
