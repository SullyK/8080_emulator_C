#include "arith.h"
// TODO: NAME EACH FUNC TO CORRESPENDING ENTRY ON DATABOOK EXAMPLE
// DCR M FOR decrement_memory

// TODO: this is pretty much exactly the same func as the add reg, I will remove
// these two and make and similar one but for now its seperate for simplicity
// skipped testing for this reason
void add_data(CPU *cpu, uint8_t byte_two) { //ADI data

  uint8_t result = cpu->registers.A + byte_two;
  cpu->flags.AC = aux_carry_sub(cpu->registers.A, byte_two);
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

  return;
}

void add_register(CPU *cpu, uint8_t reg_value) { //ADD r
  uint8_t result = cpu->registers.A + reg_value;

  cpu->flags.AC = aux_carry_add(cpu->registers.A, reg_value);
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

  return;
}

// TODO: Write a helper function which takes in two 8 bit registers and make its
// a 16 bit, and make unit tests
void add_memory(CPU *cpu, uint16_t HL) { // ADD M

  uint8_t carry = unsigned_addition_carry_check(
      cpu->registers.A, cpu->memory[HL]); // TODO: I can
                                          // probably make
                                          // this more
                                          // efficent, since
                                          // it's been done
                                          // twice

  cpu->flags.AC = aux_carry_add(cpu->registers.A, cpu->memory[HL]);
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

  return;
}

void add_register_carry(CPU *cpu, uint8_t reg_value) { //ADC r

  // TODO: figure a way to refactor this and the non-carry version
  uint8_t result = cpu->registers.A + reg_value + (uint8_t)cpu->flags.C;

  cpu->flags.AC =
      aux_carry_add_with_flag(cpu->registers.A, reg_value, cpu->flags.C);

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

  return;
}

void add_memory_carry(CPU *cpu, uint16_t HL) { //ADC M
  // TODO: DO HELPER FUNC TO COMBINE HL BEFORE PLACING INTO FUNC

  // TODO: figure a way to refactor this and the non-carry version

  uint8_t result = cpu->registers.A + cpu->memory[HL] + (uint8_t)cpu->flags.C;

  cpu->flags.AC =
      aux_carry_add_with_flag(cpu->registers.A, cpu->memory[HL], cpu->flags.C);

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

  return;
}

void add_data_carry(CPU *cpu, uint8_t byte_two) { //ACI data

  // TODO: Function to extract byte_two
  // TODO: result + carry = done similar thing twice, make more efficent
  uint8_t result = cpu->registers.A + byte_two + cpu->flags.C;
  uint8_t carry = unsigned_addition_carry_check_with_carry(
      cpu->registers.A, byte_two, (uint8_t)cpu->flags.C);
  // TODO: @@@ I think I need to do this as uint8_t cast because it will do
  // addition with uint_8

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

void subtract_register(CPU *cpu, uint8_t reg_value) { //SUB r
  uint8_t carry = unsigned_subtract_carry_check(cpu->registers.A, reg_value);

  cpu->flags.AC = aux_carry_sub(cpu->registers.A, reg_value);
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
  return;
}

void subtract_data(CPU *cpu, uint8_t byte_two) { // SUI data

  uint8_t result = cpu->registers.A - byte_two;
  uint8_t carry = unsigned_subtract_carry_check(cpu->registers.A, byte_two);
  cpu->flags.AC = aux_carry_sub(cpu->registers.A, byte_two);
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
  return;
}

void subtract_memory(CPU *cpu, uint16_t HL) { //SUB M

  uint8_t result = cpu->registers.A - cpu->memory[HL];
  uint8_t carry =
      unsigned_subtract_carry_check(cpu->registers.A, cpu->memory[HL]);

  cpu->flags.AC = aux_carry_sub(cpu->registers.A, cpu->memory[HL]);
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

  return;
}

void subtract_register_carry(CPU *cpu, uint8_t register_value) { //SBB r
  uint8_t result = cpu->registers.A - register_value - cpu->flags.C;
  uint8_t carry = unsigned_subtract_carry_check_with_carry(
      cpu->registers.A, register_value, cpu->flags.C);

  cpu->flags.AC =
      aux_carry_sub_with_flag(cpu->registers.A, register_value, cpu->flags.C);
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

  return;
}

void subtract_memory_carry(CPU *cpu, uint16_t HL) { //SBB M
  uint8_t result = cpu->registers.A - cpu->memory[HL] - cpu->flags.C;
  uint8_t carry = unsigned_subtract_carry_check_with_carry(
      cpu->registers.A, cpu->memory[HL], cpu->flags.C);

  cpu->flags.AC =
      aux_carry_sub_with_flag(cpu->registers.A, cpu->memory[HL], cpu->flags.C);

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
  return;
}

void subtract_data_carry(
    CPU *cpu, uint8_t byte_two) { //SBI data
    // TODO: helper func to determine 2nd byte
                                  // from HL register automatically
  uint8_t result = cpu->registers.A - byte_two - cpu->flags.C;
  uint8_t carry = unsigned_subtract_carry_check_with_carry(
      cpu->registers.A, byte_two, cpu->flags.C);
  cpu->flags.AC =
      aux_carry_sub_with_flag(cpu->registers.A, byte_two, cpu->flags.C);

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
  return;
}

void increment_register(CPU *cpu, uint8_t *reg) {//INR r
    // NEED to pass in a register
                                                  // e.g &cpu.registers.A

  uint8_t result = (*reg) + 1;
  cpu->flags.AC = aux_carry_add((*reg), 1);
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

  return;
}

void increment_memory(CPU *cpu, uint16_t HL) { //INR M
  uint8_t result = cpu->memory[HL] + 1;
  cpu->flags.AC = aux_carry_add(cpu->memory[HL], 1);
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

  return;
}

void decrement_register(CPU *cpu, uint8_t *reg) { // DCR r
    // NEED to pass in a register
                                                  // e.g &cpu.registers.A
  cpu->flags.AC = aux_carry_sub(*reg,1);
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

  return;
}

void decrement_memory(CPU *cpu, uint16_t HL) { //DCR M
  uint8_t result = cpu->memory[HL] - 1;
  cpu->memory[HL] = result;
  cpu->flags.AC = aux_carry_sub(cpu->memory[HL],1);
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
 return;
}

// TODO: it looks like this function just takes 2 values, we will need to
// provide the CPU->reg when calling. IDK if this is the best way to do deal
// with it but for now, we will just continue, tomorrow's problem for tomorrow
//
// thought's a little later: these are basically just 2 registers, so
// cpu->registers.B etc so shoudlnt make too much diff
void increment_register_pair(uint8_t *high,
                             uint8_t *low) { // TODO: correct order?
                                             // this shoudl take 2
                                             // register pairs which we
                                             // will edit
  uint16_t combined_reg = combine_registers(*high, *low); // combine
  combined_reg = combined_reg + 1;
  SplitBytes sb = split_bytes(combined_reg); // split @@@TODO: write tests for
                                             // these helper functions
  *high = sb.high;
  *low = sb.low;
  return; //@@@ TODO: probably better to return something.
}

void decrement_register_pair(uint8_t *high, uint8_t *low) { //DCX rp
  uint16_t combined_reg = combine_registers(*high, *low);
  combined_reg = combined_reg - 1;
  SplitBytes sb = split_bytes(combined_reg);
  *high = sb.high;
  *low = sb.low;
  return;
}

//@@@TODO: maybe just take the combined pair here?
// makes more sense, but do it in refactors
// and will need to change the test
void add_reg_pair_to_HL(CPU *cpu, uint8_t high, uint8_t low) { //DAD rp
  uint16_t combined_reg = combine_registers(high, low);
  uint16_t combined_hl = combine_registers(cpu->registers.H, cpu->registers.L);
  uint16_t added_hl = combined_reg + combined_hl;
  SplitBytes sb = split_bytes(added_hl);
  cpu->registers.H = sb.high;
  cpu->registers.L = sb.low;
  uint8_t carry_check =
      unsigned_addition_carry_check_16_bit(combined_hl, combined_reg);
  if (carry_check == 1) {
    cpu->flags.C = 1;
  } else {
    cpu->flags.C = 0;
  }
  return;
}

void decimal_adjust_accumulator(CPU *cpu) { // DAA
  if ((cpu->registers.A & 0x0F) > 9 || cpu->flags.AC == 1) {
    uint8_t carry = unsigned_addition_carry_check(cpu->registers.A, 6);
    if (carry) {
      cpu->flags.C = 1;
    } // don't think we set 0, might affecct things if no carry occurs here and
      // it is reset, because of this else
    cpu->registers.A = cpu->registers.A + 6;
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
  cpu->flags.S = check_signed_bit(cpu->registers.A);
  cpu->flags.Z = zero(cpu->registers.A);
  cpu->flags.P = check_parity(cpu->registers.A);

  if ((cpu->registers.A >> 4) > 9 || cpu->flags.C == 1) {
    uint8_t high_bits = cpu->registers.A >> 4;
    uint8_t low_bits = cpu->registers.A & 0xF;
    high_bits += 6;
    cpu->registers.A = (high_bits << 4) | low_bits;
    cpu->flags.C = 1;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    //@@@ TODO: THIS whole function is sus as hell,
    // need to properly do this and see if I ddi it properly
    cpu->flags.AC = (high_bits > 0x0F) ? 1 : 0;
  } else {
    cpu->flags.C = 0;
  }
}
