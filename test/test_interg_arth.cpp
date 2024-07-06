#include "../src/add_funcs.h"
#include "../src/art.h"
#include "../src/cpu.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(add_register_1, ExampleTest) {

  // typedef struct CPU {
  //   Flags flags;
  //   Registers registers;
  //   uint16_t SP;
  //   uint16_t PC;
  //   uint8_t memory[MEMORY_SIZE];
  // } CPU;
  CPU cpu = {0};
  cpu.registers.A = 100;
  uint8_t register_value = 100;
  add_register(&cpu, register_value);
  ASSERT_EQ(cpu.registers.A, 200);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_register_2, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 230;
  uint8_t register_value = 100;
  add_register(&cpu, register_value);
  ASSERT_EQ(cpu.registers.A, 74);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 1);
}

TEST(add_register_3, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 20;
  uint8_t register_value = 40;
  add_register(&cpu, register_value);
  ASSERT_EQ(cpu.registers.A, 60);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}

//add memory function tests
TEST(add_memory_1, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 10;
  uint16_t HL_value = 64230;
  cpu.memory[64230] = 23;
  add_memory(&cpu, HL_value);
  ASSERT_EQ(cpu.registers.A, 33);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_memory_2, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 2;
  uint16_t HL_value = 64230;
  cpu.memory[HL_value] = 255;
  add_memory(&cpu, HL_value);
  ASSERT_EQ(cpu.registers.A, 1); // overflow to 1 (not 0)
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_memory_3, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 1;
  uint16_t HL_value = 0;
  cpu.memory[HL_value] = 255;
  add_memory(&cpu, HL_value);
  ASSERT_EQ(cpu.registers.A, 0);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_memory_4, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 255;
  uint16_t HL_value = 40000;
  cpu.memory[HL_value] = 1;
  add_memory(&cpu, HL_value);
  ASSERT_EQ(cpu.registers.A, 0);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_memory_5, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 100;
  uint16_t HL_value = 40000;
  cpu.memory[HL_value] = 100;
  add_memory(&cpu, HL_value);
  ASSERT_EQ(cpu.registers.A, 200);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
}
//think of other cases for these functions

// void add_register(CPU *cpu, uint8_t reg_value);
