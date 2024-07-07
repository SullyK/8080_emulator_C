#ifndef ART_H
#define ART_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UINT_8_MAX_VALUE 255
#define UINT_8_MIN_VALUE 0

uint8_t unsigned_addition_carry_check(uint8_t a, uint8_t b);
uint8_t unsigned_addition_carry_check_with_carry(uint8_t a, uint8_t b,
                                                 uint8_t c);
uint8_t unsigned_subtract_carry_check(uint8_t a, uint8_t b);
uint8_t check_signed_bit(uint8_t number);
uint8_t check_parity(uint8_t number);
uint8_t set_aux_carry(uint8_t number);
uint8_t zero(uint8_t number);

#ifdef __cplusplus
}
#endif

#endif
