#include "logic.h"

//@@@TODO: should I actually pass the register here?
// don't really see the point, but ill come back to this
// in the main loop
void and_register(CPU *cpu, uint8_t reg) {
  cpu->registers.A = cpu->registers.A & reg;
  cpu->flags.C = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.AC = aux_carry_add(cpu->registers.A, reg);
  cpu->flags.Z = zero(cpu->registers.A);
}

void and_memory(CPU *cpu, uint16_t HL) {
  cpu->registers.A = cpu->registers.A & cpu->memory[HL];
  cpu->flags.C = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.AC = aux_carry_add(cpu->registers.A, cpu->memory[HL]);
  cpu->flags.Z = zero(cpu->registers.A);
}

void and_immediate(CPU *cpu, uint8_t byte) {
  cpu->registers.A = cpu->registers.A & byte;
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}

void exclusive_or_register(CPU *cpu, uint8_t reg) {
  cpu->registers.A = cpu->registers.A ^ reg;
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}

void exclusive_or_memory(CPU *cpu, uint16_t HL) {
  cpu->registers.A = cpu->registers.A ^ cpu->memory[HL];
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}

void exclusive_or_immediate(CPU *cpu, uint8_t byte) {
  cpu->registers.A = cpu->registers.A ^ byte;
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}

void or_register(CPU *cpu, uint8_t reg) {
  cpu->registers.A = cpu->registers.A | reg;
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}
void or_memory(CPU *cpu, uint16_t HL) {
  cpu->registers.A = cpu->registers.A | cpu->memory[HL];
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}

void or_immediate(CPU *cpu, uint8_t byte) {
  cpu->registers.A = cpu->registers.A | byte;
  cpu->flags.C = 0;
  cpu->flags.AC = 0;
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
}

void compare_register(CPU *cpu, uint8_t reg) {
  cpu->flags.C = unsigned_subtract_carry_check(cpu->registers.A, reg);
  uint8_t result = cpu->registers.A - reg;
  cpu->flags.AC = aux_carry_sub(cpu->registers.A, reg);
  cpu->flags.S = check_signed_bit(result);
  cpu->flags.P = check_parity(result);
  cpu->flags.Z = zero(result);
}

void compare_memory(CPU *cpu, uint16_t HL) {
  cpu->flags.C =
      unsigned_subtract_carry_check(cpu->registers.A, cpu->memory[HL]);
  uint8_t result = cpu->registers.A - cpu->memory[HL];
  cpu->flags.AC = aux_carry_sub(cpu->registers.A, cpu->memory[HL]);
  cpu->flags.S = check_signed_bit(result);
  cpu->flags.P = check_parity(result);
  cpu->flags.Z = zero(result);
}

void compare_immediate(CPU *cpu, uint8_t byte_two) {
  cpu->flags.C = unsigned_subtract_carry_check(cpu->registers.A, byte_two);
  uint8_t result = cpu->registers.A - byte_two;
  cpu->flags.AC = aux_carry_sub(cpu->registers.A, byte_two);
  cpu->flags.S = check_signed_bit(result);
  cpu->flags.P = check_parity(result);
  cpu->flags.Z = zero(result);
}

void rotate_left(CPU *cpu) {
  uint8_t extracted_bit = cpu->registers.A >> 7 & 0x01;
  cpu->registers.A = cpu->registers.A << 1;
  cpu->registers.A = cpu->registers.A | extracted_bit;
  cpu->flags.C = extracted_bit;
}

void rotate_right(CPU *cpu) {
  uint8_t extracted_bit = cpu->registers.A & 0x1;
  cpu->registers.A = cpu->registers.A >> 1;
  cpu->registers.A = cpu->registers.A | (extracted_bit << 7);
  cpu->flags.C = extracted_bit;
}

void rotate_left_carry(CPU *cpu) {
  uint8_t extracted_bit = cpu->registers.A >> 7 & 0x01;
  cpu->registers.A = cpu->registers.A << 1;
  cpu->registers.A = cpu->registers.A | cpu->flags.C;
  cpu->flags.C = extracted_bit;
}

void rotate_right_carry(CPU *cpu) {
  uint8_t extracted_bit = cpu->registers.A & 0x01;
  cpu->registers.A = cpu->registers.A >> 1;
  cpu->registers.A = cpu->registers.A | (cpu->flags.C << 7);
  cpu->flags.C = extracted_bit;
}

void complement_accumulator(CPU *cpu) {
    cpu->registers.A = ~(cpu->registers.A);
}

void complement_carry(CPU *cpu) {
    cpu->flags.C = ~(cpu->flags.C);
}

void set_carry(CPU *cpu) {
    cpu->flags.C = 1;
}
