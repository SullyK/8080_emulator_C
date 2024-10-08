#include "../src/cpu.h"
#include "../src/flags.h"
#include "../src/logic.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(and_register, NoChange) {
  CPU cpu = {0};
  cpu.registers.A = 0xA;
  uint8_t fake_register = 0xA;
  and_register(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0xA);
}

TEST(and_register, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 50;
  uint8_t fake_register = 200;
  and_register(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0x0);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(and_register, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0xFF;
  uint8_t fake_register = 0x1;
  and_register(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0x1);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(and_register, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0x0F;
  uint8_t fake_register = 0xF0;
  and_register(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0x00);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(and_register, Basic4) {
  CPU cpu = {0};
  cpu.registers.A = 0xFF;
  uint8_t fake_register = 0xFF;
  and_register(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0xFF);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(and_register, Basic5) {
  CPU cpu = {0};
  cpu.registers.A = 0x0;
  uint8_t fake_register = 0x0;
  and_register(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0x0);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(and_memory, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b11001100;
  uint16_t dummy_HL = 54000;
  cpu.memory[dummy_HL] = 0b10001101;
  and_memory(&cpu, dummy_HL);
  ASSERT_EQ(cpu.registers.A, 0b10001100);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(and_memory, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint16_t dummy_HL = 54;
  cpu.memory[dummy_HL] = 0b11111111;
  and_memory(&cpu, dummy_HL);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(and_immediate, Basic1ACExpected0) {
  CPU cpu = {0};
  cpu.registers.A = 0xFF;
  uint8_t fake_register = 0xFF;
  and_immediate(&cpu, fake_register);
  ASSERT_EQ(cpu.registers.A, 0xFF);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_register, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint8_t example_register = 0b11111111;
  exclusive_or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_register, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b11110000;
  uint8_t example_register = 0b00001111;
  exclusive_or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_register, Basic2Swapped) {
  CPU cpu = {0};
  cpu.registers.A = 0b00001111;
  uint8_t example_register = 0b11110000;
  exclusive_or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_register, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint8_t example_register = 0b11111111;
  exclusive_or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b01111110);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(exclusive_or_register, Basic4) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint8_t example_register = 0b00000000;
  exclusive_or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(exclusive_or_memory, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint16_t dummy_HL = 54;
  cpu.memory[dummy_HL] = 0b11111111;
  exclusive_or_memory(&cpu, dummy_HL);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_memory, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b10101010;
  uint16_t dummy_HL = 54;
  cpu.memory[dummy_HL] = 0b01010101;
  exclusive_or_memory(&cpu, dummy_HL);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_memory, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0b10101010;
  uint16_t dummy_HL = 54;
  cpu.memory[dummy_HL] = 0b01010101;
  exclusive_or_memory(&cpu, dummy_HL);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

//@@@ TODO: these TESTS are 100% the same as the exclusive_or_register but I
// needed to make tests for this in case I swap those to take actual register
// values, i haven't decided yet, will do in main loop. Point is this is here
// for now incase I make changes to that later
TEST(exclusive_or_immediate, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint8_t example_register = 0b11111111;
  exclusive_or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_immediate, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b11110000;
  uint8_t example_register = 0b00001111;
  exclusive_or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_immediate, Basic2Swapped) {
  CPU cpu = {0};
  cpu.registers.A = 0b00001111;
  uint8_t example_register = 0b11110000;
  exclusive_or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(exclusive_or_immediate, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint8_t example_register = 0b11111111;
  exclusive_or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b01111110);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(exclusive_or_immediate, Basic4) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint8_t example_register = 0b00000000;
  exclusive_or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(or_register, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint8_t example_register = 0b00000000;
  or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(or_register, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  uint8_t example_register = 0b00000000;
  or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_register, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  uint8_t example_register = 0b11111111;
  or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_register, Basic4) {
  CPU cpu = {0};
  cpu.registers.A = 0b10101010;
  uint8_t example_register = 0b01010101;
  or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_register, Basic5) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint8_t example_register = 0b01010101;
  or_register(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11010101);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_memory, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint16_t HL = 1000;
  cpu.memory[HL] = 0b10001111;
  or_memory(&cpu, HL);
  ASSERT_EQ(cpu.registers.A, 0b10001111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_memory, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  uint16_t HL = 1000;
  cpu.memory[HL] = 0b00000000;
  or_memory(&cpu, HL);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

//@@@ TODO: exact same as register tests, but immediate
TEST(or_immediate, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  uint8_t example_register = 0b00000000;
  or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(or_immediate, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  uint8_t example_register = 0b00000000;
  or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_immediate, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  uint8_t example_register = 0b11111111;
  or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_immediate, Basic4) {
  CPU cpu = {0};
  cpu.registers.A = 0b10101010;
  uint8_t example_register = 0b01010101;
  or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(or_immediate, Basic5) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint8_t example_register = 0b01010101;
  or_immediate(&cpu, example_register);
  ASSERT_EQ(cpu.registers.A, 0b11010101);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(compare_register, BigMinusSmall) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint8_t example_register = 0b01010101;
  compare_register(&cpu, example_register);
  // expected value: 0b00101100
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(compare_register, SmallSubtractBig) {
  CPU cpu = {0};
  cpu.registers.A = 0b0;
  uint8_t example_register = 0b11111111;
  compare_register(&cpu, example_register);
  // expected value: 0b1
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(compare_register, AccuSameNumberAsRegister) {
  CPU cpu = {0};
  cpu.registers.A = 0b00001111;
  uint8_t example_register = 0b00001111;
  compare_register(&cpu, example_register);
  // expected value: 0b0
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(compare_memory, BigMinusSmall) {
  CPU cpu = {0};
  cpu.registers.A = 0x4F;
  uint16_t HL = 0xFFAA;
  cpu.memory[HL] = 0x0F;
  compare_memory(&cpu, HL);
  // expected value: 0b1000000 (64 decimal)
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(compare_memory, SmallMinusBigTriggerACAndUnderflow) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000111;
  uint16_t HL = 0xFFAA;
  cpu.memory[HL] = 0b00001000;
  compare_memory(&cpu, HL);
  // expected value: 0b11111111 (255 decimal - underflow)
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(compare_memory, AccSameAsMemorySize) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  uint16_t HL = 0xFFAA;
  cpu.memory[HL] = 0b11111111;
  compare_memory(&cpu, HL);
  // expected value: 0b0
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(compare_immediate, BigMinusSmall) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000001;
  uint8_t example_register = 0b01010101;
  compare_immediate(&cpu, example_register);
  // expected value: 0b00101100
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(compare_immediate, SmallSubtractBig) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000111;
  uint8_t example_register = 0b00001000;
  compare_immediate(&cpu, example_register);
  // expected value: 0b11111111 (255 - underflow)
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.S, 1);
}

TEST(compare_immediate, AccuSameNumberAsRegister) {
  CPU cpu = {0};
  cpu.registers.A = 0b00001111;
  uint8_t example_register = 0b00001111;
  compare_immediate(&cpu, example_register);
  // expected value: 0b0
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.S, 0);
}

TEST(rotate_left, Basic1) {
  CPU cpu = {0};
  cpu.registers.A = 0b10000000;
  rotate_left(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000001);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_left, Basic2) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000001;
  rotate_left(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000010);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left, Basic3) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  rotate_left(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_left, Basic4) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  rotate_left(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left, Basic5) {
  CPU cpu = {0};
  cpu.registers.A = 0b00111100;
  rotate_left(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b01111000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left, Basic6) {
  CPU cpu = {0};
  cpu.registers.A = 0b01111111;
  rotate_left(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b11111110);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_right, Test1) {
  CPU cpu = {0};
  cpu.registers.A = 0b000000001;
  rotate_right(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b10000000);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_right, Test2) {
  CPU cpu = {0};
  cpu.registers.A = 0b011000000;
  rotate_right(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b01100000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_right, Test3) {
  CPU cpu = {0};
  cpu.registers.A = 0b011111111;
  rotate_right(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b11111111);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_right, Test4) {
  CPU cpu = {0};
  cpu.registers.A = 0b00000000;
  rotate_right(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b000000000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_right, Test5) {
  CPU cpu = {0};
  cpu.registers.A = 0b10101010;
  rotate_right(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b01010101);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left_carry, Test1) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.registers.A = 0b10001001;
  rotate_left_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00010011);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_left_carry, Test2) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.registers.A = 0b10001001;
  rotate_left_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00010010);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_left_carry, Test3) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.registers.A = 0b00001001;
  rotate_left_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00010011);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left_carry, Test4) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.registers.A = 0b00001001;
  rotate_left_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00010010);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left_carry, Test5) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.registers.A = 0b00000000;
  rotate_left_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_left_carry, Test6) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.registers.A = 0b00000000;
  rotate_left_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000001);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_right_carry, Test1) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.registers.A = 0b00000000;
  rotate_right_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b10000000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_right_carry, Test2) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.registers.A = 0b00000001;
  rotate_right_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_right_carry, Test3) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.registers.A = 0b00000001;
  rotate_right_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b10000000);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(rotate_right_carry, Test4) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.registers.A = 0b10000000;
  rotate_right_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b11000000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(rotate_right_carry, Test5) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.registers.A = 0b10000000;
  rotate_right_carry(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b01000000);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(comp_acc, Test1) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  complement_accumulator(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
}

TEST(comp_acc, Test2) {
  CPU cpu = {0};
  cpu.registers.A = 0b11111111;
  complement_accumulator(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b00000000);
}

TEST(comp_acc, Test3) {
  CPU cpu = {0};
  cpu.registers.A = 0b01010101;
  complement_accumulator(&cpu);
  ASSERT_EQ(cpu.registers.A, 0b10101010);
}

TEST(comp_carry, Test1) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  complement_carry(&cpu);
  ASSERT_EQ(cpu.flags.C, 0);
}

TEST(comp_carry, Test2) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  complement_carry(&cpu);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(set_carry, Test1) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  set_carry(&cpu);
  ASSERT_EQ(cpu.flags.C, 1);
}

TEST(set_carry, Test2) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  set_carry(&cpu);
  ASSERT_EQ(cpu.flags.C, 1);
}
