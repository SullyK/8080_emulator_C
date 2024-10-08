#include "branch.h"
#include <stdlib.h>

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
    cpu->PC = (high_byte << 8) | low_byte;
    cpu->SP = cpu->SP + 2;
  }

  return;
}
