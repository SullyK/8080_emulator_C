#ifndef HELPERS
#define HELPERS
#include "art.h"
#include "cpu.h"
#include <stdint.h>
                              
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t high;
    uint8_t low;
} SplitBytes;


uint16_t combine_registers(uint8_t high_byte, uint8_t low_byte);
SplitBytes split_bytes(uint16_t value); //rename this to a better name, it's 16 bit value 
#ifdef __cplusplus
}
#endif

#endif

