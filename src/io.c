#include "io.h"

void push_rp(CPU *cpu, uint16_t rp) {
  cpu->memory[cpu->SP - 1] = rp >> 8;
  cpu->memory[cpu->SP - 2] = rp & 0xFF;
  cpu->SP -= 2;
}

void push_psw(CPU *cpu) {
  cpu->memory[cpu->SP - 1] = cpu->registers.A;
  uint8_t psw = (cpu->flags.S << 7) | (cpu->flags.Z << 6) | (0 << 5) |
                (cpu->flags.AC << 4) | (0 << 3) | (cpu->flags.P << 2) |
                (1 << 1) | (cpu->flags.C);
  cpu->memory[(cpu->SP) - 2] = psw;
  cpu->SP -= 2;
}

void pop_rp(CPU *cpu, uint16_t *rp) {
  *rp = (cpu->memory[cpu->SP + 1] << 8) | cpu->memory[cpu->SP];
  cpu->SP += 2;
}

void pop_psw(CPU *cpu) {
  cpu->flags.C = cpu->memory[cpu->SP] & 0x1;
  cpu->flags.P = (cpu->memory[cpu->SP] >> 2) & 0x1;
  cpu->flags.AC = (cpu->memory[cpu->SP] >> 4) & 0x1;
  cpu->flags.Z = (cpu->memory[cpu->SP] >> 6) & 0x1;
  cpu->flags.S = (cpu->memory[cpu->SP] >> 7) & 0x1;
  cpu->registers.A = cpu->memory[cpu->SP + 1];
  cpu->SP += 2;
}

void XTHL(CPU *cpu) {
  uint8_t temp = cpu->registers.L;
  cpu->registers.L = cpu->memory[cpu->SP];
  cpu->memory[cpu->SP] = temp;

  temp = cpu->registers.H;
  cpu->registers.H = cpu->memory[cpu->SP + 1];
  cpu->memory[cpu->SP + 1] = temp;
}

void SPHL(CPU *cpu) { cpu->SP = (cpu->registers.H << 8) | cpu->registers.L; }

// MACHINE SPECIFIC - to the ARCADE MACHINE that runs SPACE INVADERS
// this can defo be optimised better
// I believe only 4 ports are used here,0,1,2 and 3-shift reg
//@@@!!!TODO: Not tested
void in_port(CPU *cpu, uint8_t port) {
  if (port == 3) {
    // do some shift-register reading here - I think...
    uint16_t combined = (cpu->shift_high << 8) | cpu->shift_low;
    cpu->registers.A = (combined >> (8 - cpu->shift_offset)) & 0xFF;
  } else {
    cpu->registers.A = port;
  }
}

//@@@!!!TODO: Not tested
void out_port(CPU *cpu, uint8_t port) {
  if (port == 2) {
    cpu->shift_offset = cpu->registers.A & 0x07;
  }
  if (port == 4) {
    cpu->shift_low = cpu->shift_high;
    cpu->shift_high = cpu->registers.A;
  }
}

//!!!@@@TODO: THESE haven't got tests -- do them
void EI(CPU *cpu) { cpu->int_pending = true; }
void DI(CPU *cpu) {
  cpu->int_enabled = false;
  cpu->int_pending = false;
}

void HLT(void) {
  printf("This should never execute at least for my purpose");
  exit(-1);
}

//@@@ TODO: See if this will be optimised out
// need to add cycle count so it WILL be necessary
void NOP(void) {}

//@@@!!!TODO: MOVE THIS LATER - to interrupt.C?
//
void gen_interrupt(CPU *cpu, uint8_t interrupt_num) {
  // push PC to stack
  //@@@TODO: do this directly no need for variables
  uint8_t PC_high = (cpu->PC >> 8) & 0xFF;
  uint8_t PC_low = cpu->PC & 0xFF;
  cpu->memory[cpu->SP - 1] = PC_high;
  cpu->memory[cpu->SP - 2] = PC_low;
  cpu->SP -= 2;

  cpu->PC = 8 * interrupt_num;
}
