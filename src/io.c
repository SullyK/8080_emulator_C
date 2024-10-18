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

void XTHL(CPU *cpu){
    uint8_t temp = cpu->registers.L;
    cpu->registers.L = cpu->memory[cpu->SP];
    cpu->memory[cpu->SP] = temp;
    
    temp = cpu->registers.H;
    cpu->registers.H = cpu->memory[cpu->SP + 1];
    cpu->memory[cpu->SP + 1] = temp;
}


void SPHL(CPU *cpu){
    cpu->SP = (cpu->registers.H << 8) | cpu->registers.L;
}

//@@@TODO: IMPLEMENT I/O -- I Might need to put this into an external file and deal with IO on a
//specific basis for the space invaders emulator
//Q: do I need an array of IO ports?
//void  in_port(CPU *cpu, uint8_t data){
//    cpu->registers.A = data;
//}
//
 //@@@TODO: IMPLEMENT I/O
//void  out_port(CPU *cpu, uint8_t *data){
 //   *data = cpu->registers.A;
//}
 


