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

// add memory function tests
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
// think of other cases for the above func

// add_register_carry func tests
TEST(add_register_carry_1, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 0;
  uint8_t reg_value = 100;
  cpu.flags.C = 1;

  add_register_carry(&cpu, reg_value);
  ASSERT_EQ(cpu.registers.A, 101);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_register_carry_2, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 244;
  uint8_t reg_value = 10;
  cpu.flags.C = 1;

  add_register_carry(&cpu, reg_value);
  ASSERT_EQ(cpu.registers.A, 255);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}

TEST(add_register_carry_3, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 0;
  uint8_t reg_value = 255;
  cpu.flags.C = 1;
  add_register_carry(&cpu, reg_value);
  ASSERT_EQ(cpu.registers.A, 0);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_register_carry_4, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 255;
  uint8_t reg_value = 0;
  cpu.flags.C = 1;
  add_register_carry(&cpu, reg_value);
  ASSERT_EQ(cpu.registers.A, 0);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_register_carry_5, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 255;
  uint8_t reg_value = 0;
  cpu.flags.C = 0;
  add_register_carry(&cpu, reg_value);
  ASSERT_EQ(cpu.registers.A, 255);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}

// add_memory_carry tests
TEST(add_memory_carry_1, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 0;
  cpu.flags.C = 1;
  uint16_t HL = 2000;
  cpu.memory[HL] = 20;
  add_memory_carry(&cpu, HL);
  ASSERT_EQ(cpu.registers.A, 21);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_memory_carry_2, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 150;
  cpu.flags.C = 0;
  uint16_t HL = 2000;
  cpu.memory[HL] = 20;
  add_memory_carry(&cpu, HL);
  ASSERT_EQ(cpu.registers.A, 170);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}

TEST(add_memory_carry_3, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 255;
  cpu.flags.C = 1;
  uint16_t HL = 65535;
  cpu.memory[HL] = 255;
  add_memory_carry(&cpu, HL);
  ASSERT_EQ(cpu.registers.A, 255);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}

// add_data_carry tests

TEST(add_data_carry_1, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 99;
  cpu.flags.C = 1;
  uint8_t byte_two = 10;
  add_data_carry(&cpu, byte_two);
  ASSERT_EQ(cpu.registers.A, 110);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 1);
}

TEST(add_data_carry_2, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 255;
  cpu.flags.C = 1;
  uint8_t byte_two = 40;
  add_data_carry(&cpu, byte_two);
  ASSERT_EQ(cpu.registers.A, 40);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_data_carry_3, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 0;
  cpu.flags.C = 0;
  uint8_t byte_two = 0;
  add_data_carry(&cpu, byte_two);
  ASSERT_EQ(cpu.registers.A, 0);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 1);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(add_data_carry_4, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 100;
  cpu.flags.C = 1;
  uint8_t byte_two = 200;
  add_data_carry(&cpu, byte_two);
  ASSERT_EQ(cpu.registers.A, 45);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}

 
TEST(add_data_carry_5, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 100;
  cpu.flags.C = 1;
  uint8_t byte_two = 200;
  add_data_carry(&cpu, byte_two);
  ASSERT_EQ(cpu.registers.A, 45);
  ASSERT_EQ(cpu.flags.C, 1);
  ASSERT_EQ(cpu.flags.S, 0);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 1);
  ASSERT_EQ(cpu.flags.AC, 1);
}                                                 
                                                  
 
TEST(add_data_carry_6, ExampleTest) {
  CPU cpu = {0};
  cpu.registers.A = 100;
  cpu.flags.C = 1;
  uint8_t byte_two = 80;
  add_data_carry(&cpu, byte_two);
  ASSERT_EQ(cpu.registers.A, 181);
  ASSERT_EQ(cpu.flags.C, 0);
  ASSERT_EQ(cpu.flags.S, 1);
  ASSERT_EQ(cpu.flags.Z, 0);
  ASSERT_EQ(cpu.flags.P, 0);
  ASSERT_EQ(cpu.flags.AC, 0);
} 

TEST(subtract_register_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 200;
    uint8_t test_register = 50;
    subtract_register(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 150);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}

 
TEST(subtract_register_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 255;
    uint8_t test_register = 255;
    subtract_register(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 0);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 1);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
} 

TEST(subtract_register_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 10;
    uint8_t test_register = 20;
    subtract_register(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 246);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
} 
 
TEST(subtract_memory_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 100;
    cpu.registers.H = 20;
    cpu.registers.L = 10;
    uint16_t temp_16_bit_test = (cpu.registers.H << 8) | cpu.registers.L;
    cpu.memory[5130] = 1;
    subtract_memory(&cpu, temp_16_bit_test);
    ASSERT_EQ(cpu.registers.A, 99);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 0); //@@@ TODO: sanity check - meant to be  right?
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
} 

 
TEST(subtract_memory_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 255;
    uint16_t HL_placeholder = 200;
    cpu.memory[HL_placeholder] = 122;
    subtract_memory(&cpu,HL_placeholder);
    ASSERT_EQ(cpu.registers.A,133);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
} 
 
TEST(subtract_memory_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 0;
    uint16_t HL_placeholder = 500;
    cpu.memory[HL_placeholder] = 1;
    subtract_memory(&cpu,HL_placeholder);
    ASSERT_EQ(cpu.registers.A,255); //@@@ TODO: ARE THESE FLAGS CORRECT?
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
} 

TEST(subtract_register_carry_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 10;
    cpu.flags.C = 1;
    uint8_t test_register = 1;
    subtract_register_carry(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 8);//@@@ TODO: ARE THESE FLAGS CORRECT?
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}
 
TEST(subtract_register_carry_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 10;
    cpu.flags.C = 1;
    uint8_t test_register = 0;
    subtract_register_carry(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 9);//@@@ TODO: ARE THESE FLAGS CORRECT?
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}
 
 
 
// void add_register(CPU *cpu, uint8_t reg_value);
