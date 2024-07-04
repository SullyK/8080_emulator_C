#include "art.h"
#include "cpu.h"

uint8_t unsigned_addition_carry_check(uint8_t a, uint8_t b) {
  if (a > 0 && b > (UINT_8_MAX_VALUE - a)) { // overflow set
    return 1;
  }
  return 0;
}

uint8_t unsigned_subtract_carry_check(uint8_t a, uint8_t b) {
  if (a < b) { // underflow set
    return 1;
  }
  return 0;
}

uint8_t check_signed_bit(uint8_t number) {
  if ((number >> 7)) { // TODO: I don't think I need == 1, should be 0 or 1
    return 1;
  }

  return 0;
}

uint8_t check_parity(uint8_t number) {
  uint8_t counter = 0;
  for (int x = 0; x < 8; x++) {
    if ((number >> x) & 1) {
      counter++;
    }
  }
  return (counter % 2 == 0) ? 1 : 0;
}

uint8_t set_aux_carry(uint8_t number) { // naive implementation
  int extract_half_byte = number & 0xf;

  if (extract_half_byte > 9) {
    return 1;
  }

  return 0;
}

uint8_t zero(uint8_t number) {
  if (number) {
    return 0;
  }
  return 1;
}

int add_register(CPU *cpu, uint8_t reg_value) {

  uint8_t result = unsigned_addition_carry_check(cpu->registers.A, reg_value);
  cpu->registers.A = result;
  // carry
  if (result) {
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

  return 0;
}
