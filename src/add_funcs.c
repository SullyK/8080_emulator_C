#include "add_funcs.h"

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
