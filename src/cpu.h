#ifndef CPU_H
#define CPU_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MEMORY_SIZE 65536 // 64KiB

#ifdef _cpluscplus
extern "C" {
#endif

typedef struct Flags {
  unsigned int S : 1;
  unsigned int Z : 1;
  unsigned int P : 1;
  unsigned int C : 1;
  unsigned int AC : 1;
} Flags;

typedef struct Registers {
  uint8_t A;
  uint8_t B;
  uint8_t C;
  uint8_t D;
  uint8_t E;
  uint8_t H;
  uint8_t L;
} Registers;

typedef struct CPU {
  Flags flags;
  Registers registers;
  uint16_t SP;
  uint16_t PC;
  uint8_t memory[MEMORY_SIZE];
  bool int_enabled;
  uint8_t shift_offset;
  uint8_t shift_low;
  uint8_t shift_high;
  uint8_t in_ports[8]; //I don't know if this is necessary yet, might need to keep it for
		       //keybord in to write to it
} CPU;

#ifdef _cplusplus
}
#endif 

#endif
