#include "io.h"

void push_rp(CPU *cpu, uint16_t rp) {
  cpu->memory[cpu->SP - 1] = rp >> 8;
  cpu->memory[cpu->SP - 2] = rp & 0xFF;
  cpu->SP -= 2;
}

void push_psw(CPU *cpu) {
  cpu->memory[cpu->SP - 1] = cpu->registers.A;
  uint8_t psw = (cpu->flags.S << 7) |
      (cpu->flags.Z << 6) | (0 << 5) |
      (cpu->flags.AC << 4) | (0 << 3) | 
      (cpu->flags.P << 2) | (1 << 1)  | 
      (cpu->flags.C);
  cpu->memory[(cpu->SP) - 2] = psw;
  cpu->SP -= 2;
}

void pop_rp(CPU *cpu, uint16_t *rp) {
  *rp = (cpu->memory[cpu->SP + 1] << 8) | cpu->memory[cpu->SP];
  cpu->SP += 2;
}

void pop_psw(CPU *cpu){
    cpu->flags.C = cpu->memory[cpu->SP] & 0x1;
    cpu->flags.P = (cpu->memory[cpu->SP] >> 2) & 0x1;
    cpu->flags.AC = (cpu->memory[cpu->SP] >> 4) & 0x1;
    cpu->flags.Z = (cpu->memory[cpu->SP] >> 6) & 0x1;
    cpu->flags.S = (cpu->memory[cpu->SP] >> 7) & 0x1;
    cpu->registers.A = cpu->memory[cpu->SP + 1];
    cpu->SP += 2;
}


