#include "helpers.h"
#include "cpu.h"
#include "art.h"

uint16_t combine_registers(uint8_t high_byte, uint8_t low_byte){
    return (high_byte << 8) | low_byte
}
