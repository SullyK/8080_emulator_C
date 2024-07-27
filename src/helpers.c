#include "helpers.h"

uint16_t combine_registers(uint8_t high_byte, uint8_t low_byte){
    return (high_byte << 8) | low_byte;
}

SplitBytes split_bytes(uint16_t value){
    SplitBytes sb; 
    sb.high = value >> 8;
    sb.low = value & 0xFF;
    return sb;
}

