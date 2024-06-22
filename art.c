#include <art.h>

int overflow_detected(uint8_t a,
                      uint8_t b) { // This checks for uint8_t overflows
  if (a > 0 && b > (UINT_8_MAX_VALUE - a)) { // TODO: Write tests for this func
    // printf("OVERFLOW");
    return 1;
  }

  return 0;
}

int check_signed_bit(uint8_t number) {
  if ((number >> 7)) { // TODO: I don't think I need == 1, should be 0 or 1
    return 1
  }

  return 0;
}

uint8_t check_parity(uint8_t number) {
  // TODO: resume here, figure out how parity stuff works.
  uint8_t counter = 0;
  for (int x = 0; x < 8; x++) {
    if ((number >> x) & 1) {
      counter++;
    }
  }
  return (counter % 2 == 0) ? 1 : 0;
}

int set_aux_carry(int number) { // naive implementation
  int extract_half_byte = number & 0xf;

  if (extract_half_byte > 9) {
    return 1;
  }

  return 0;
}

int add_register(*CPU cpu, uint8_t reg_value) {

  uint8_t result = overflow_detected(cpu->registers.A + reg_value);
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
  if (result) {
    cpu->flags.Z = 0;
  } else {
    cpu->flags.Z = 1;
  }

  // parity
  if (check_parity(number)) {
    cpu->flags.P = 1;
  } else {
    cpu->flags.P = 0;
  }

  // aux carry TODO: figure out how this BCD and DAA aux carry stuff works.
  // Resume here.
  if (set_aux_carry(number)) {
    cpu->flags.AC = 1;
  } else {
    cpu->flags.AC = 0;
  }
}
