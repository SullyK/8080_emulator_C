#include "branch.h"
#include <stdlib.h>

void jmp_addr(CPU *cpu, int high_byte, int low_byte) {
  cpu->PC = (high_byte << 8) | low_byte;
}

void conditional_jump(CPU *cpu, int high_byte, int low_byte,
                      uint8_t condition) {
  bool condition_met = 0;
  switch (condition) {
  case 0:
    condition_met = (cpu->flags.Z == 0);
    break;
  case 1:
    condition_met = (cpu->flags.Z == 1);
    break;
  case 2:
    condition_met = (cpu->flags.C == 0);
    break;
  case 3:
    condition_met = (cpu->flags.C == 1);
    break;
  case 4:
    condition_met = (cpu->flags.P == 0);
    break;
  case 5:
    condition_met = (cpu->flags.P == 1);
    break;
  case 6:
    condition_met = (cpu->flags.S == 0);
    break;
  case 7:
    condition_met = (cpu->flags.S == 1);
    break;
  default:
    printf(
        "Couldn't find the jump you were looking for, conditional_jump func\n");
  }

  if (condition_met) {
    cpu->PC = (high_byte << 8) | low_byte;
  } else {
    cpu->PC += 3;
  }
}

void call_addr(CPU *cpu, int high_byte, int low_byte) {
  cpu->SP = cpu->SP - 2;
  cpu->memory[cpu->SP] = (cpu->PC >> 8);
  cpu->memory[cpu->SP + 1] = (cpu->PC & 0xFF);
  cpu->PC = (high_byte << 8) | low_byte;
}

void conditional_call(CPU *cpu, int high_byte, int low_byte,
                      uint8_t condition) {

  bool condition_met = 0;
  switch (condition) {
  case 0:
    condition_met = (cpu->flags.Z == 0);
    break;
  case 1:
    condition_met = (cpu->flags.Z == 1);
    break;
  case 2:
    condition_met = (cpu->flags.C == 0);
    break;
  case 3:
    condition_met = (cpu->flags.C == 1);
    break;
  case 4:
    condition_met = (cpu->flags.P == 0);
    break;
  case 5:
    condition_met = (cpu->flags.P == 1);
    break;
  case 6:
    condition_met = (cpu->flags.S == 0);
    break;
  case 7:
    condition_met = (cpu->flags.S == 1);
    break;
  default:
    printf(
        "Couldn't find the jump you were looking for, conditional_call func\n");
  }

  if (condition_met) {
    cpu->SP = cpu->SP - 2;
    cpu->memory[cpu->SP] = (cpu->PC >> 8);
    cpu->memory[cpu->SP + 1] = (cpu->PC & 0xFF);
    cpu->PC = (high_byte << 8) | low_byte;
  } else {
    cpu->PC += 3;
  }
}

void branch_return(CPU *cpu) {
  uint8_t low_byte = cpu->memory[cpu->SP];
  uint8_t high_byte = cpu->memory[(cpu->SP) + 1];
  cpu->PC = (high_byte << 8) | (low_byte & 0xFF);
  cpu->SP = cpu->SP + 2;
}

void conditional_branch_return(CPU *cpu, uint8_t condition) {

  // Make a proper jump table here later

  bool condition_met = 0;

  switch (condition) {
  case 0:
    condition_met = (cpu->flags.Z == 0);
    break;
  case 1:
    condition_met = (cpu->flags.Z == 1);
    break;
  case 2:
    condition_met = (cpu->flags.C == 0);
    break;
  case 3:
    condition_met = (cpu->flags.C == 1);
    break;
  case 4:
    condition_met = (cpu->flags.P == 0);
    break;
  case 5:
    condition_met = (cpu->flags.P == 1);
    break;
  case 6:
    condition_met = (cpu->flags.S == 0);
    break;
  case 7:
    condition_met = (cpu->flags.S == 1);
    break;
  default:
    printf("you really really messed up XD\n");
    printf("exiting..\n");
    // exit(-1); // make a more portable exit (EXIT_FAILURE)
    return;
  }

  if (condition_met) {
    uint8_t low_byte = cpu->memory[cpu->SP];
    uint8_t high_byte = cpu->memory[(cpu->SP) + 1];
    cpu->PC = (high_byte << 8) | (low_byte & 0xFF);
    cpu->SP = cpu->SP + 2;
  } else {
    cpu->PC += 1;
  }

  return;
}

void restart(CPU *cpu, uint8_t n_value) {

  cpu->memory[(cpu->SP) - 1] = cpu->PC >> 8;
  cpu->memory[(cpu->SP) - 2] = cpu->PC & 0xFF;
  cpu->SP = cpu->SP - 2;
  cpu->PC = 8 * n_value;
}

void PCHL(CPU *cpu) { cpu->PC = (cpu->registers.H << 8) | cpu->registers.L; }
