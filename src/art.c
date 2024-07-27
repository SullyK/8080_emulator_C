#include "art.h"
#include "cpu.h"

uint8_t unsigned_addition_carry_check(uint8_t a, uint8_t b) {
  if (b > (UINT_8_MAX_VALUE - a)) { // overflow set
    return 1;
  }
  return 0;
}

uint8_t unsigned_addition_carry_check_with_carry(uint8_t a, uint8_t b,
                                                 uint8_t c) { // TODO: 1)
                                                              // rename
                                                              // 2) int8_t
                                                              // or bool?
                                                              // which is
                                                              // more
                                                              // effeicent
  if ((b+c) > (UINT_8_MAX_VALUE - a)) { // overflow set
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

uint8_t unsigned_subtract_carry_check_with_carry(uint8_t a, uint8_t b, uint8_t carry) {
  if (a < b - carry) { // underflow set with carry - test this
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

// void set_all_flags_add(uint8_t a, uint8_t b, Flags *flags){}
// TODO: maybe a composite function which I can use instead of manually doing
// each one, but I will come back to it
