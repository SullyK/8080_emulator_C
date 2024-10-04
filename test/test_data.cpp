#include "../src/data.h"
#include <gtest/gtest.h>
#include <iostream>
//
//TEST(move_register, test_1) {
//  CPU cpu = {0};
//  cpu.registers.A = 100;
//  cpu.registers.B = 200;
//  move_register(&cpu.registers.B, &cpu.registers.A);
//  ASSERT_EQ(cpu.registers.A, 200);
//  ASSERT_EQ(cpu.registers.B, 200);
//}
//
//TEST(move_register, test_2) {
//  CPU cpu = {0};
//  cpu.registers.A = 0;
//  cpu.registers.B = 0;
//  move_register(&cpu.registers.B, &cpu.registers.A);
//  ASSERT_EQ(cpu.registers.A, 0);
//  ASSERT_EQ(cpu.registers.B, 0);
//}
//
//TEST(move_register, test_3) {
//  CPU cpu = {0};
//  cpu.registers.A = 0;
//  cpu.registers.B = 32;
//  move_register(&cpu.registers.B, &cpu.registers.A);
//  ASSERT_EQ(cpu.registers.A, 32);
//  ASSERT_EQ(cpu.registers.B, 32);
//}
//
//TEST(move_register, test_4) {
//  CPU cpu = {0};
//  cpu.registers.A = 250;
//  cpu.registers.B = 0;
//  move_register(&cpu.registers.B, &cpu.registers.A);
//  ASSERT_EQ(cpu.registers.A, 0);
//  ASSERT_EQ(cpu.registers.B, 0);
//}
//
//TEST(move_from_memory, test_1) {
//  CPU cpu = {0};
//  cpu.registers.C = 0;
//  uint16_t some_combined_reg = 100;
//  cpu.memory[100] = 12;
//  move_from_memory(&cpu, some_combined_reg, &cpu.registers.C);
//  ASSERT_EQ(cpu.registers.C, 12);
//}
//
//TEST(move_from_memory, test_2) {
//  CPU cpu = {0};
//  cpu.registers.B = 50;
//  uint16_t some_combined_reg = 3430;
//  cpu.memory[some_combined_reg] = 2;
//  move_from_memory(&cpu, some_combined_reg, &cpu.registers.B);
//  ASSERT_EQ(cpu.registers.B, 2);
//}
//
//TEST(move_to_memory, test_1) {
//  CPU cpu = {0};
//  cpu.registers.C = 43;
//  uint16_t some_combined_reg = 100;
//  cpu.memory[some_combined_reg] = 12;
//  move_to_memory(&cpu, &cpu.registers.C, some_combined_reg);
//  ASSERT_EQ(cpu.memory[some_combined_reg], 43);
//}
//
//TEST(move_immediate, test_1) {
//  CPU cpu = {0};
//  cpu.registers.A = 255;
//  uint8_t byte_two = 200;
//  move_immediate(byte_two, &cpu.registers.A);
//  ASSERT_EQ(cpu.registers.A, 200);
//  ASSERT_EQ(byte_two, 200);
//}
//
//TEST(move_immediate_to_memory, test_1) {
//  CPU cpu = {0};
//  uint8_t byte_two = 66;
//  uint16_t some_combined_reg = 100;
//  cpu.memory[some_combined_reg] = 2;
//  move_immediate_to_memory(&cpu, byte_two, some_combined_reg);
//  ASSERT_EQ(cpu.memory[some_combined_reg], 66);
//  ASSERT_EQ(byte_two, 66);
//}
//TEST(load_reg_pair_immed, test_1) {
//  CPU cpu = {0};
//  uint8_t byte_three = 0b00001111;
//  uint8_t byte_two = 0b11110000;
//  // should be combined to 0b0000111111110000
//  cpu.registers.B = 0xFF;
//  cpu.registers.C = 0xFF;
//  uint16_t BC = combine_registers(cpu.registers.B, cpu.registers.A);
//  load_reg_pair_immed(byte_three, byte_two, &BC);
//  ASSERT_EQ(BC, 0b0000111111110000);
//}
//
//TEST(load_reg_pair_immed, test_2) {
//  CPU cpu = {0};
//  uint8_t byte_three = 0b00001111;
//  uint8_t byte_two = 0b11110000;
//  // should be combined to 0b0000111111110000
//  cpu.registers.B = 0xFF;
//  cpu.registers.C = 0xFF;
//  uint16_t BC = combine_registers(cpu.registers.B, cpu.registers.A);
//  load_reg_pair_immed(byte_three, byte_two, &BC);
//  ASSERT_EQ(BC, 0b0000111111110000);
//}
//
//TEST(load_reg_pair_immed, test_3) {
//  CPU cpu = {0};
//  uint8_t byte_three = 0b11111000;
//  uint8_t byte_two = 0b00001111;
//  // should be combined to 0b0000111111110000
//  cpu.registers.B = 0xFF;
//  cpu.registers.C = 0xFF;
//  uint16_t BC = combine_registers(cpu.registers.B, cpu.registers.A);
//  load_reg_pair_immed(byte_three, byte_two, &BC);
//  ASSERT_EQ(BC, 0b1111111100001111);
//}
//
//TEST(load_acc_direct, test_1) {
//  CPU cpu = {0};
//  uint8_t byte_three = 0b11111111;
//  uint8_t byte_two = 0b00000000;
//  cpu.registers.A = 20;
//  uint16_t combined = combine_registers(byte_three, byte_two);
//  cpu.memory[combined] = 177;
//  load_acc_direct(&cpu, byte_three, byte_two);
//  ASSERT_EQ(cpu.registers.A, 177);
//}
//
//TEST(load_h_l_direct, test_1) {
//  CPU cpu = {0};
//  uint8_t byte_three = 0b11111111; // 0xFF
//  uint8_t byte_two = 0b00000000;   // 0x00
//  cpu.registers.A = 20;
//  uint16_t combined = combine_registers(byte_three, byte_two); // 0xFF00
//  ASSERT_EQ(combined, 0xFF00);
//  cpu.memory[combined] = 40;
//  cpu.memory[combined + 1] = 111;
//  load_h_l_direct(&cpu, byte_three, byte_two);
//  ASSERT_EQ(cpu.registers.L, 40);
//  ASSERT_EQ(cpu.registers.H, 111);
//}
//
//TEST(store_h_l_direct, test_1) {
//  CPU cpu = {0};
//  uint8_t byte_three = 0b11111111; // 0xFF
//  uint8_t byte_two = 0b00000000;   // 0x00
//  cpu.registers.L = 99;
//  cpu.registers.L = 200;
//  uint16_t combined = combine_registers(byte_three, byte_two); // 0xFF00
//  ASSERT_EQ(combined, 0xFF00);
//  cpu.memory[combined] = 40;
//  cpu.memory[combined + 1] = 111;
//  store_h_l_direct(&cpu, byte_three, byte_two);
//  ASSERT_EQ(cpu.registers.L, 99);
//  ASSERT_EQ(cpu.registers.H, 200);
//}
//
//TEST(load_acc_indirect, test_1) {
//  CPU cpu = {0};
//  uint16_t rp_value = 39400;
//  cpu.memory[rp_value] = 222;
//  cpu.registers.A = 1;
//  load_acc_indirect(&cpu, rp_value);
//  ASSERT_EQ(cpu.registers.A, 222);
//  ASSERT_EQ(rp_value, 39400);
//}
//
//TEST(store_acc_indirect, test_1) {
//  CPU cpu = {0};
//  uint16_t rp_value = 39400;
//  cpu.memory[rp_value] = 222;
//  cpu.registers.A = 1;
//  store_acc_indirect(&cpu, rp_value);
//  ASSERT_EQ(cpu.registers.A, 1);
//  ASSERT_EQ(rp_value, 39400);
//}
//
//TEST(exchange_hl_with_de, test_1) {
//  CPU cpu = {0};
//  cpu.registers.H = 222;
//  cpu.registers.L = 111;
//
//  cpu.registers.D = 100;
//  cpu.registers.E = 200;
//  exchange_hl_with_de(&cpu);
//  ASSERT_EQ(cpu.registers.H, 100);
//  ASSERT_EQ(cpu.registers.L, 200);
//
//  ASSERT_EQ(cpu.registers.D, 222);
//  ASSERT_EQ(cpu.registers.E, 111);
//}
