#ifndef ART_H
#define ART_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UINT_8_MAX_VALUE 255
#define UINT_8_MIN_VALUE 0

uint8_t overflow_detected(uint8_t a,uint8_t b);

#ifdef __cplusplus
}
#endif

#endif
