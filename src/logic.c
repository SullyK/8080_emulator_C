#include "logic.h"


void and_register(CPU *cpu, uint8_t reg){
    cpu->registers.A = cpu->registers.A & reg;
    cpu->flags.C = 0;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    cpu->flags.AC = set_aux_carry(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
}
