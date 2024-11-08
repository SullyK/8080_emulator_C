#include "arith.h"
#include "branch.h"
#include "cpu.h"
#include "data.h"
#include "flags.h"
#include "helpers.h"
#include "io.h"
#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
uint8_t opcodeSizes[256];

int opcode_size(uint8_t opcode) { return opcodeSizes[opcode]; }

void update_PC(uint8_t number, CPU *cpu) { cpu->PC += number; }
void init_opcodes_sizes_array(void) {
  for (int x = 0; x < 256; x++) {
    opcodeSizes[x] = 1;
  }

  opcodeSizes[0x01] = 3;
  opcodeSizes[0x11] = 3;
  opcodeSizes[0x21] = 3;
  opcodeSizes[0x22] = 3;
  opcodeSizes[0x2a] = 3;
  opcodeSizes[0x31] = 3;
  opcodeSizes[0x32] = 3;
  opcodeSizes[0x3a] = 3;
  opcodeSizes[0xc2] = 3;
  opcodeSizes[0xc3] = 3;
  opcodeSizes[0xc4] = 3;
  opcodeSizes[0xca] = 3;
  opcodeSizes[0xcc] = 3;
  opcodeSizes[0xcd] = 3;
  opcodeSizes[0xd2] = 3;
  opcodeSizes[0xd4] = 3;
  opcodeSizes[0xda] = 3;
  opcodeSizes[0xdc] = 3;
  opcodeSizes[0xe2] = 3;
  opcodeSizes[0xe4] = 3;
  opcodeSizes[0xea] = 3;
  opcodeSizes[0xec] = 3;
  opcodeSizes[0xf2] = 3;
  opcodeSizes[0xf4] = 3;
  opcodeSizes[0xfa] = 3;
  opcodeSizes[0xfc] = 3;

  opcodeSizes[0x06] = 2;
  opcodeSizes[0x0e] = 2;
  opcodeSizes[0x16] = 2;
  opcodeSizes[0x1e] = 2;
  opcodeSizes[0x26] = 2;
  opcodeSizes[0x2e] = 2;
  opcodeSizes[0x36] = 2;
  opcodeSizes[0x3e] = 2;
  opcodeSizes[0xc6] = 2;
  opcodeSizes[0xce] = 2;
  opcodeSizes[0xd3] = 2;
  opcodeSizes[0xd6] = 2;
  opcodeSizes[0xdb] = 2;
  opcodeSizes[0xde] = 2;
  opcodeSizes[0xe6] = 2;
  opcodeSizes[0xee] = 2;
  opcodeSizes[0xf6] = 2;
  opcodeSizes[0xfe] = 2;
}

// Last time I did this, I read the whole thing
// in chunks to try and be less error prone
// this was a hassle...
// for now I will just read it directly into a malloc array

// THIS CODE IS NOT REALLY SAFE BECAUSE fopen DOESN'T SUPPORT
// binary streams but for my purposes it's fine...
// because I want it to work on all OS and don't want to use
// platform specific API
void read_file_into_mem(CPU *cpu) {
  // For now this will be hardcoded - for testing
  FILE *fp = fopen("invaders.rom", "rb");
  if (fp == NULL) {
    printf("error in reading your file\n");
    exit(-1);
  }

  fseek(fp, 0, SEEK_END);
  // overkill?
  uint64_t file_length = ftell(fp);
  printf("file_length = %llu", file_length);
  fseek(fp, 0, SEEK_SET);

  uint8_t *buffer = malloc(file_length);
  if (buffer == NULL) {
    printf("Failed to alloc memory\n");
    exit(-1);
  }
  uint64_t data_read = fread(buffer, 1, file_length, fp);
  printf("data_read = %llu\n", data_read);
  if (data_read == file_length) {
    printf("reading file ran correctly\n");
  } else {
    if (feof(fp)) {
      printf("error: unexpected feof\n");
      exit(-1);
    } else if (ferror(fp)) {
      perror("error reading file");
      exit(-1);
    }
  }
  fclose(fp);
  memcpy(cpu->memory, buffer, file_length);
  free(buffer);

  //!!!@@@TODO: Remove Malloc entirely, known file lenght or error out
  // for now just assume it's safe
  // add checks later

  return;
}

int main(void) {

  // init
  CPU cpu = {0};
  read_file_into_mem(&cpu);
  init_opcodes_sizes_array();
  uint8_t op = 0;

  // this is really not going to be great but i didn't think too hard about
  // how i designed it so i will just implement it as is and maybe refactor it

  for (;;) {
    // need to do the checking for interrupts somewhere at the start or end...
    //

    printf("cpu.PC value: %d\n", cpu.PC);

    op = cpu.memory[cpu.PC];
    switch (op) {
    case 0x00:
    case 0x08:
    case 0x10:
    case 0x18:
    case 0x20:
    case 0x28:
    case 0x30:
    case 0x38:
      NOP();
      update_PC(opcode_size(op), &cpu);
      // write a cycles func later
      break;

    case 0x01: {
      uint16_t bc = (cpu.registers.B << 8) | cpu.registers.C;
      load_reg_pair_immed(cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], &bc);
      cpu.registers.B = bc >> 8;
      cpu.registers.C = bc & 0xFF;
      if (cpu.registers.B != 0) {
        printf("BUFFER B Contents: %u\n", cpu.registers.B);
      }
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x11: {
      uint16_t de = (cpu.registers.D << 8) | cpu.registers.E;
      load_reg_pair_immed(cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], &de);
      cpu.registers.D = de >> 8;
      cpu.registers.E = de & 0xFF;
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x21: {
      uint16_t hl = (cpu.registers.H << 8) | cpu.registers.L;
      load_reg_pair_immed(cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], &hl);
      cpu.registers.H = hl >> 8;
      cpu.registers.L = hl & 0xFF;
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x31: {
      load_reg_pair_immed(cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1],
                          &cpu.SP);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x02: {
      uint16_t BC = combine_registers(cpu.registers.B, cpu.registers.C);
      store_acc_indirect(&cpu, BC);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x12: {
      uint16_t DE = combine_registers(cpu.registers.D, cpu.registers.E);
      store_acc_indirect(&cpu, DE);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x22: {
      store_h_l_direct(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x32: {
      store_acc_direct(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }

      // INX
    case 0x03: {
      increment_register_pair(&cpu.registers.B, &cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x13: {

      increment_register_pair(&cpu.registers.D, &cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x23: {
      increment_register_pair(&cpu.registers.H, &cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x33: {
      uint8_t high = (cpu.SP >> 8) & 0XFF;
      uint8_t low = cpu.SP & 0XFF;
      increment_register_pair(&high, &low);
      cpu.SP = combine_registers(high, low);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    // INR
    case 0x04: {
      increment_register(&cpu, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x14: {
      increment_register(&cpu, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x24: {
      increment_register(&cpu, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x34: {
      // check if this properly works or is just dumb
      increment_memory(&cpu,
                       combine_registers(cpu.registers.H, cpu.registers.L));
      update_PC(opcode_size(op), &cpu);
      break;
    }

    // DCR
    case 0x05: {
      decrement_register(&cpu, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x15: {
      decrement_register(&cpu, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x25: {
      decrement_register(&cpu, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x35: {
      // check if this properly works or is just dumb
      decrement_memory(&cpu,
                       combine_registers(cpu.registers.H, cpu.registers.L));
      update_PC(opcode_size(op), &cpu);
      break;
    }

    // MVI
    case 0x06: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x16: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x26: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x36: {
      // check if this properly works or is just dumb
      move_immediate_to_memory(
          &cpu, cpu.memory[cpu.PC + 1],
          combine_registers(cpu.registers.H, cpu.registers.L));
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x07: {
      rotate_left(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x17: {
      rotate_left_carry(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x27: {
      decimal_adjust_accumulator(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x37: {
      set_carry(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }
      // 0x08->0x38 == NOP so skipped as done @ start

    case 0x09: {
      add_reg_pair_to_HL(&cpu, cpu.registers.B, cpu.registers.C);

      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x19: {
      add_reg_pair_to_HL(&cpu, cpu.registers.D, cpu.registers.E);

      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x29: {
      add_reg_pair_to_HL(&cpu, cpu.registers.H, cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x39: {
      add_reg_pair_to_HL(&cpu, ((cpu.SP >> 8) & 0xFF), (cpu.SP & 0xFF));
      update_PC(opcode_size(op), &cpu);

      break;
    }

    case 0x0A: {
      load_acc_indirect(&cpu,
                        combine_registers(cpu.registers.B, cpu.registers.C));
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x1A: {
      load_acc_indirect(&cpu,
                        combine_registers(cpu.registers.D, cpu.registers.E));
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x2A: {
      load_h_l_direct(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x3A: {
      load_acc_direct(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x0B: {
      decrement_register_pair(&cpu.registers.B, &cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x1B: {
      decrement_register_pair(&cpu.registers.C, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x2B: {
      decrement_register_pair(&cpu.registers.H, &cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x3B: {
      // special case just modify directly
      cpu.SP -= 1;
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x0C: {
      increment_register(&cpu, &cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x1C: {

      increment_register(&cpu, &cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x2C: {

      increment_register(&cpu, &cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x3C: {
      increment_register(&cpu, &cpu.registers.A);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x0D: {
      decrement_register(&cpu, &cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x1D: {

      decrement_register(&cpu, &cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x2D: {

      decrement_register(&cpu, &cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x3D: {
      decrement_register(&cpu, &cpu.registers.A);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x0E: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x1E: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x2E: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x3E: {
      move_immediate(cpu.memory[cpu.PC + 1], &cpu.registers.A);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x0F: {
      rotate_right(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x1F: {
      rotate_right_carry(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x2F: {
      complement_accumulator(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0x3F: {
      complement_carry(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    // Above is the first four rows, doing rows 4 to F now (rest) per set
    case 0x40: { // B -> B
      move_register(&cpu.registers.B, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x50: { // B -> D
      move_register(&cpu.registers.B, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x60: { // B -> H
      move_register(&cpu.registers.B, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x70: { // B -> memory[HL]
      move_to_memory(&cpu, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x80: { // ADD B
      add_register(&cpu, cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x90: { // SUB B
      subtract_register(&cpu, cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA0: { // ANA B
      and_register(&cpu, cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB0: { // ORA B
      or_register(&cpu, cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    //  @@@!!!TODO: refactor later - these have bad param names and conditions.
    //  The mappings SUCK
    case 0xC0: { // RNZ - 0
      conditional_branch_return(&cpu, 0);
      break;
    }
    case 0xD0: { // RNC - 2
      conditional_branch_return(&cpu, 2);
      break;
    }
    case 0xE0: { // RPO - 4
      conditional_branch_return(&cpu, 4);
      break;
    }
    case 0xF0: { // RP - 6
      conditional_branch_return(&cpu, 6);
      break;
    }

      // column 1(starts from 0), rows 4 to F

    case 0x41: { // C -> B
      move_register(&cpu.registers.C, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x51: { // C -> D
      move_register(&cpu.registers.C, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x61: { // C -> H
      move_register(&cpu.registers.C, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x71: { // C -> memory[HL]
      move_to_memory(&cpu, &cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x81: { // ADD C
      add_register(&cpu, cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x91: { // SUB C
      subtract_register(&cpu, cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA1: { // ANA C
      and_register(&cpu, cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB1: { // ORA C
      or_register(&cpu, cpu.registers.C);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xC1: { // POP B (BC)
                 // add error handling if BC has
                 // issues in debugging laterg
      uint16_t BC = 0;
      pop_rp(&cpu, &BC);
      SplitBytes sb = split_bytes(BC);
      cpu.registers.B = sb.high;
      cpu.registers.C = sb.low;
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xD1: { // POP D (DE)
                 // add error handling if BC has
                 // issues in debugging laterg
      uint16_t DE = 0;
      pop_rp(&cpu, &DE);
      SplitBytes sb = split_bytes(DE);
      cpu.registers.D = sb.high;
      cpu.registers.E = sb.low;

      update_PC(opcode_size(op), &cpu);

      break;
    }

    case 0xE1: { // POP H (HL)
                 // add error handling if BC has
                 // issues in debugging laterg
      uint16_t HL = 0;
      pop_rp(&cpu, &HL);
      SplitBytes sb = split_bytes(HL);
      cpu.registers.H = sb.high;
      cpu.registers.L = sb.low;

      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xF1: {
      pop_psw(&cpu);

      update_PC(opcode_size(op), &cpu);
      break;
    }

      // column 2 (3rd on the table), rows 4->F
    case 0x42: { // D -> B
      move_register(&cpu.registers.D, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x52: { // D -> D
      move_register(&cpu.registers.D, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x62: { // D -> H
      move_register(&cpu.registers.D, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x72: { // D -> memory[HL]
      move_to_memory(&cpu, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x82: { // ADD D
      add_register(&cpu, cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x92: { // SUD D
      subtract_register(&cpu, cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA2: { // ANA D
      and_register(&cpu, cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB2: { // ORA D
      or_register(&cpu, cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xC2: { // JNZ
      conditional_jump(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 0);
      break;
    }
    case 0xD2: { // JNC
      conditional_jump(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 2);
      break;
    }
    case 0xE2: { // JPO
      conditional_jump(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 4);
      break;
    }
    case 0xF2: { // JP
      conditional_jump(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 6);
      break;
    }

    // column 3 (4th from left) - rows 4->F
    case 0x43: { // E -> B
      move_register(&cpu.registers.E, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x53: { // E -> D
      move_register(&cpu.registers.E, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x63: { // E -> H
      move_register(&cpu.registers.E, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x73: { // E -> memory[HL]
      move_to_memory(&cpu, &cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x83: { // ADD E
      add_register(&cpu, cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x93: { // SUB E
      subtract_register(&cpu, cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA3: { // ANA E
      and_register(&cpu, cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB3: { // ORA E
      or_register(&cpu, cpu.registers.E);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xC3: { // JMP
      jmp_addr(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }
      //@@@!!!TODO: skipped this below case for now - IO
      //    case 0xD3: {
      //		   break;
      //    }

    case 0xE3: {
      XTHL(&cpu);
      update_PC(opcode_size(op), &cpu);
    }

      //@@@!!!TODO: skipped this below case for now - IO
      //    case 0xF3: {
      //      break;
      //    }
      //
      //--------------------------------------

    // column 4 (5 from the right), rows 4->f
    case 0x44: { // H -> B
      move_register(&cpu.registers.H, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x54: { // H -> D
      move_register(&cpu.registers.H, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x64: { // H -> H
      move_register(&cpu.registers.H, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x74: { // H -> memory[HL]
      move_to_memory(&cpu, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x84: { // ADD H
      add_register(&cpu, cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x94: { // SUB H
      subtract_register(&cpu, cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA4: { // ANA H
      and_register(&cpu, cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB4: { // ORA H
      or_register(&cpu, cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xC4: {
      conditional_call(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 0);
      break;
    }

    case 0xD4: {
      conditional_call(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 2);
      break;
    }

    case 0xE4: {
      conditional_call(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 4);
      break;
    }

    case 0xF4: {
      conditional_call(&cpu, cpu.memory[cpu.PC + 2], cpu.memory[cpu.PC + 1], 6);
      break;
    }

      // Column 6 (5th from left) - rows 4->F

    case 0x45: { // L -> B
      move_register(&cpu.registers.L, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x55: { // L -> D
      move_register(&cpu.registers.L, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x65: { // L -> H
      move_register(&cpu.registers.L, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x75: { // L -> memory[HL]
      move_to_memory(&cpu, &cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x85: { // ADD L
      add_register(&cpu, cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x95: { // SUB L
      subtract_register(&cpu, cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA5: { // ANA L
      and_register(&cpu, cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB5: { // ORA L
      or_register(&cpu, cpu.registers.L);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xC5: { // PUSH B (BC)
                 // add error handling if BC has
                 // issues in debugging laterg
      uint16_t BC = (cpu.registers.B << 8) | cpu.registers.C;
      push_rp(&cpu, BC);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xD5: { // PUSH D (DE)
                 // add error handling if BC has
                 // issues in debugging laterg
      uint16_t DE = (cpu.registers.D << 8) | cpu.registers.E;
      push_rp(&cpu, DE);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xE5: { // PUSH H (HL)
                 // add error handling if BC has
                 // issues in debugging laterg
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      push_rp(&cpu, HL);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xF5: {
      push_psw(&cpu);
      update_PC(opcode_size(op), &cpu);
      break;
    }

      // Column 7 (6th from left) - rows 4->F
      //
    case 0x46: { // memory[HL] -> B
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      move_from_memory(&cpu, HL, &cpu.registers.B);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x56: { // memory[HL]  -> D
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      move_from_memory(&cpu, HL, &cpu.registers.D);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x66: { // memory[HL] -> H
      move_register(&cpu.registers.H, &cpu.registers.H);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x76: { // HLT
      HLT();
      break;
    }
    case 0x86: { // ADD M memory[HL] to accum, store accum
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      add_memory(&cpu, HL);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0x96: { // SUB M memory[HL] from accum, store in acc
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      subtract_memory(&cpu, HL);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xA6: { // ANA M
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      subtract_memory(&cpu, HL);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xB6: { // ORA M
      uint16_t HL = (cpu.registers.H << 8) | cpu.registers.L;
      or_memory(&cpu, HL);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xC6: { // ADI d8
      add_data(&cpu, cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xD6: { // ADI d8
      subtract_data(&cpu, cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    case 0xE6: { // ANI d8
      and_immediate(&cpu, cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }
    case 0xF6: { // ORI d8
      or_immediate(&cpu, cpu.memory[cpu.PC + 1]);
      update_PC(opcode_size(op), &cpu);
      break;
    }

    default:
      break;

      // end of switch statement
    }

    // end of for loop
  }
}
