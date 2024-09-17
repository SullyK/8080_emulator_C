#include "logic.h"

//@@@TODO: should I actually pass the register here?
//don't really see the point, but ill come back to this 
//in the main loop
void and_register(CPU *cpu, uint8_t reg){
    cpu->registers.A = cpu->registers.A & reg;
    cpu->flags.C = 0;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    cpu->flags.AC = set_aux_carry(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
}

void and_memory(CPU *cpu, uint16_t HL){
    cpu->registers.A = cpu->registers.A & cpu->memory[HL];
    cpu->flags.C = 0;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    cpu->flags.AC = set_aux_carry(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
}

void and_immediate(CPU *cpu, uint8_t byte){
    cpu->registers.A = cpu->registers.A & byte;
    cpu->flags.C = 0;
    cpu->flags.AC = 0;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
}

void exclusive_or_register(CPU *cpu, uint8_t reg){
    cpu->registers.A = cpu->registers.A ^ reg;
    cpu->flags.C = 0;
    cpu->flags.AC = 0;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
}

void exclusive_or_memory(CPU *cpu, uint16_t HL){
    cpu->registers.A = cpu->registers.A ^ cpu->memory[HL];
    cpu->flags.C = 0;
    cpu->flags.AC = 0;
    cpu->flags.S = check_signed_bit(cpu->registers.A);
    cpu->flags.P = check_parity(cpu->registers.A);
    cpu->flags.Z = zero(cpu->registers.A);
}

void exclusive_or_immediate(CPU *cpu, uint8_t byte){
     cpu->registers.A = cpu->registers.A ^ byte;
     cpu->flags.C = 0;
     cpu->flags.AC = 0;
     cpu->flags.S = check_signed_bit(cpu->registers.A);
     cpu->flags.P = check_parity(cpu->registers.A);
     cpu->flags.Z = zero(cpu->registers.A);
 }
							   

