#include "data.h"

void move_register(uint8_t *src, uint8_t *dest) {
  *dest = *src;
  return;
}

void move_from_memory(CPU *cpu, uint16_t src, uint8_t *dest) {
  *dest = cpu->memory[src];
  return;
}
void move_to_memory(CPU *cpu, uint8_t *src, uint16_t dest) {
  cpu->memory[dest] = *src;
  return;
}

void move_immediate(uint8_t src, uint8_t *dest) {
  *dest = src;
  return;
}

void move_immediate_to_memory(CPU *cpu, uint8_t src, uint16_t dest) {
  cpu->memory[dest] = src;
  return;
}

void load_reg_pair_immed(uint8_t reg_high, uint8_t reg_low,
                         uint16_t *register_pair) {

  *register_pair = (reg_high << 8) | reg_low;
  return;
}
void load_acc_direct(CPU *cpu, uint8_t reg_high, uint8_t reg_low) {
  cpu->registers.A = cpu->memory[((reg_high << 8) | reg_low)];
}

void store_acc_direct(CPU *cpu, uint8_t high_byte, uint8_t low_byte) {
  cpu->memory[((high_byte << 8) | low_byte)] = cpu->registers.A;
}

void load_h_l_direct(CPU *cpu, uint8_t reg_high, uint8_t reg_low) {
  uint16_t combined = (reg_high << 8) | reg_low;
  cpu->registers.L = cpu->memory[combined];
  cpu->registers.H = cpu->memory[combined + 1];
}

void store_h_l_direct(CPU *cpu, uint8_t high_byte, uint8_t low_byte) {
  uint16_t combined = (high_byte << 8) | low_byte;
  cpu->memory[combined] = cpu->registers.L;
  cpu->memory[combined + 1] = cpu->registers.H;
}

void load_acc_indirect(CPU *cpu, uint16_t register_pair) {
  cpu->registers.A = cpu->memory[register_pair];
}

void store_acc_indirect(CPU *cpu, uint16_t register_pair) {
  //@@@TODO - this will require condition in main loop only for rp BC and rp DE
  // to be used
  cpu->memory[register_pair] = cpu->registers.A;
}

void exchange_hl_with_de(CPU *cpu) {
  // could do fancy xor swap but maybe it will confuse compiler with
  // optimisation - probably can do direct swap with some cool instruction
  uint8_t temp = cpu->registers.D;
  cpu->registers.D = cpu->registers.H;
  cpu->registers.H = temp;
  temp = cpu->registers.E;
  cpu->registers.E = cpu->registers.L;
  cpu->registers.L = temp;
}
