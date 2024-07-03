#ifndef ART_H
#define ART_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UINT_8_MAX_VALUE 255
#define UINT_8_MIN_VALUE 0

uint8_t overflow_detected(uint8_t a,uint8_t b);
uint8_t check_signed_bit(uint8_t number);
uint8_t check_parity(uint8_t number);
uint8_t set_aux_carry(uint8_t number);
uint8_t zero(uint8_t number);

#ifdef __cplusplus
}
#endif

#endif
