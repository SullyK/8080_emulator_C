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
  result = check_signed_bit(result);
  if (result) {
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

}
