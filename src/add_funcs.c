#include "add_funcs.h"
#include "helpers.h"
// TODO: NAME EACH FUNC TO CORRESPENDING ENTRY ON DATABOOK EXAMPLE
// DCR M FOR decrement_memory

// TODO: this is pretty much exactly the same func as the add reg, I will remove
// these two and make and similar one but for now its seperate for simplicity
// skipped testing for this reason
void add_data(CPU *cpu, uint8_t byte_two) {

  uint8_t result = cpu->registers.A + byte_two;
  uint8_t carry = unsigned_addition_carry_check(cpu->registers.A,
                                                byte_two); // TODO: I can
                                                           // probably make
                                                           // this more
                                                           // efficent, since
                                                           // it's been done
                                                           // twice

  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

void add_register(CPU *cpu, uint8_t reg_value) {

  uint8_t result = cpu->registers.A + reg_value;
  uint8_t carry = unsigned_addition_carry_check(cpu->registers.A,
                                                reg_value); // TODO: I can
                                                            // probably make
                                                            // this more
                                                            // efficent, since
                                                            // it's been done
                                                            // twice

  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

// TODO: Write a helper function which takes in two 8 bit registers and make its
// a 16 bit, and make unit tests
void add_memory(CPU *cpu, uint16_t HL) {

  uint8_t carry = unsigned_addition_carry_check(
      cpu->registers.A, cpu->memory[HL]); // TODO: I can
                                          // probably make
                                          // this more
                                          // efficent, since
                                          // it's been done
                                          // twice

  uint8_t result = cpu->memory[HL] + cpu->registers.A;
  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void add_register_carry(CPU *cpu, uint8_t reg_value) {

  // TODO: figure a way to refactor this and the non-carry version
  uint8_t result = cpu->registers.A + reg_value + (uint8_t)cpu->flags.C;

  uint8_t carry = unsigned_addition_carry_check_with_carry(
      cpu->registers.A, reg_value, (uint8_t)cpu->flags.C);
  // Carry = and result = same operation really, probably can optimise it
  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

void add_memory_carry(CPU *cpu, uint16_t HL) {
  // TODO: DO HELPER FUNC TO COMBINE HL BEFORE PLACING INTO FUNC

  // TODO: figure a way to refactor this and the non-carry version

  uint8_t result = cpu->registers.A + cpu->memory[HL] + (uint8_t)cpu->flags.C;

  uint8_t carry = unsigned_addition_carry_check_with_carry(
      cpu->registers.A, cpu->memory[HL], (uint8_t)cpu->flags.C);
  // Carry = and result = same operation really, probably can optimise it
  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

void add_data_carry(CPU *cpu, uint8_t byte_two) {

  // TODO: Function to extract byte_two
  // TODO: result + carry = done similar thing twice, make more efficent
  uint8_t result = cpu->registers.A + byte_two + cpu->flags.C;
  uint8_t carry = unsigned_addition_carry_check_with_carry(
      cpu->registers.A, byte_two, (uint8_t)cpu->flags.C);

  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

void subtract_register(CPU *cpu, uint8_t reg_value) {
  uint8_t carry = unsigned_subtract_carry_check(cpu->registers.A, reg_value);
  uint8_t result = cpu->registers.A - reg_value;
  cpu->registers.A = result;

  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void subtract_data(CPU *cpu, uint8_t byte_two) {

  uint8_t result = cpu->registers.A - byte_two;
  uint8_t carry = unsigned_subtract_carry_check(cpu->registers.A, byte_two);
  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

void subtract_memory(CPU *cpu, uint16_t HL) {

  uint8_t result = cpu->registers.A - cpu->memory[HL];
  uint8_t carry = unsigned_subtract_carry_check(cpu->registers.A, byte_two);
  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }

  return;
}

void subtract_memory(CPU *cpu, uint16_t HL) {

  uint8_t result = cpu->registers.A - cpu->memory[HL];
  uint8_t carry = unsigned_subtract_carry_check(cpu->registers.A, byte_two);
  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void subtract_register_carry(CPU *cpu, uint8_t register_value) {
  uint8_t result = cpu->registers.A - register_value - cpu.flags.C;
  uint8_t carry = subtract_register_carry_with_carry(
      cpu->registers.A - register_value - cpu.flags.C);

  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void subtract_memory_carry(CPU *cpu, uint16_t HL) {
  uint8_t result = cpu->registers.A - cpu->memory[HL] - cpu.flags.C;
  uint8_t carry = subtract_register_carry_with_carry(
      cpu->registers.A - cpu->memory[HL] - cpu.flags.C);

  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void subtract_data_carry(
    CPU *cpu, uint8_t byte_two) { // TODO: helper func to determine 2nd byte
                                  // from HL register automatically
  uint8_t result = cpu->registers.A - byte_two - cpu.flags.C;
  uint8_t carry = subtract_register_carry_with_carry(cpu->registers.A -
                                                     byte_two - cpu.flags.C);

  cpu->registers.A = result;
  // carry
  if (carry == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }

  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void increment_register(CPU *cpu, uint8_t *reg) { // NEED to pass in a register
                                                  // e.g &cpu.registers.A
  uint8_t result = *reg + 1;
  *reg = result;
  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void increment_memory(CPU *cpu, uint16_t HL) {
  uint8_t result = cpu->memory[HL] + 1;
  cpu->memory[HL] = result;
  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void decrement_register(CPU *cpu, uint8_t *reg) { // NEED to pass in a register
                                                  // e.g &cpu.registers.A
  uint8_t result = *reg - 1;
  *reg = result;
  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void decrement_memory(CPU *cpu, uint16_t HL) {
  uint8_t result = cpu->memory[HL] - 1;
  cpu->memory[HL] = result;
  // signed
  uint8_t sign = check_signed_bit(result);
  if (sign) {
    cpu->flags.S = 1;
  } else {
    cpu->flags.S = 0;
  }

  // zero
  uint8_t zero_return = zero(result);
  cpu->flags.Z = zero_return;

  // parity
  if (check_parity(result)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry
  if (set_aux_carry(result)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  return;
}

void increment_register_pair(CPU *cpu, uint8_t *high,
                             uint8_t *low) { // TODO: correct order?
                                             // this shoudl take 2
                                             // register pairs which we
                                             // will edit
  uint16_t combined_reg = combine_registers(*high, *low);
  combined_reg = combined_reg + 1;
  //TODO: Helper splitting function
  *high = combined >> 8;
  *low = combined & 0xFF;

  return;
  //TODO: resume here:
  //1) check the helpers.h file is correct
  //2) check the helpers being properly imported
  //3) check this and other .h files proper
  //4) finish the final few functions
  //5) test them all
  
}
