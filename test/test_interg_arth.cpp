#include "../src/arith.h"
#include "../src/flags.h"
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
  ASSERT_EQ(cpu.flags.AC, 0);
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
  ASSERT_EQ(cpu.flags.AC, 0);
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
  ASSERT_EQ(cpu.flags.AC, 1);
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
  ASSERT_EQ(cpu.flags.AC, 1);
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
  ASSERT_EQ(cpu.flags.AC, 1);
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
  ASSERT_EQ(cpu.flags.AC, 1);
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
  ASSERT_EQ(cpu.flags.AC, 0);
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
  ASSERT_EQ(cpu.flags.AC, 1);
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
  ASSERT_EQ(cpu.flags.AC, 1);
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
  ASSERT_EQ(cpu.flags.AC, 0);
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
 

TEST(subtract_memory_carry_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 200;
    cpu.flags.C = 1;
    uint16_t test_register_16_bit = 60000;
    cpu.memory[test_register_16_bit] = 50;
    subtract_memory_carry(&cpu, test_register_16_bit);
    ASSERT_EQ(cpu.registers.A, 149);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}
 
TEST(subtract_memory_carry_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 255;
    cpu.flags.C = 1;
    uint16_t HL_placeholder = 200;
    cpu.memory[HL_placeholder] = 122;
    subtract_memory_carry(&cpu,HL_placeholder);
    ASSERT_EQ(cpu.registers.A,132);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
} 
 
TEST(subtract_memory_carry_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 0;
    cpu.flags.C = 0;
    uint16_t HL_placeholder = 500;
    cpu.memory[HL_placeholder] = 1;
    subtract_memory_carry(&cpu,HL_placeholder);
    ASSERT_EQ(cpu.registers.A,255); //@@@ TODO: ARE THESE FLAGS CORRECT?
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
} 
 
TEST(subtract_data_carry_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 200;
    uint8_t test_register = 50;
    cpu.flags.C = 1;
    subtract_data_carry(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 149);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}

 
TEST(subtract_data_carry_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 255;
    uint8_t test_register = 255;
    cpu.flags.C = 1;
    subtract_data_carry(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 255);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
} 

TEST(subtract_data_carry_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 10;
    uint8_t test_register = 20;
    cpu.flags.C = 1;
    subtract_data_carry(&cpu, test_register);
    ASSERT_EQ(cpu.registers.A, 245);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
} 
 
TEST(increment_register_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 10;
    increment_register(&cpu, &cpu.registers.A);
    ASSERT_EQ(cpu.registers.A, 11);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(increment_register_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 0;
    increment_register(&cpu, &cpu.registers.A);
    ASSERT_EQ(cpu.registers.A, 1);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}

 
TEST(increment_register_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 254;
    increment_register(&cpu, &cpu.registers.A);
    ASSERT_EQ(cpu.registers.A, 255);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}
  
TEST(increment_register_4, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 255;
    increment_register(&cpu, &cpu.registers.A);
    ASSERT_EQ(cpu.registers.A, 0);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 1);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
}
TEST(increment_memory_1, ExampleTest){
    CPU cpu = {0};
    uint16_t HL_test_register = 50000;
    cpu.memory[HL_test_register] = 20;
    increment_memory(&cpu, HL_test_register);
    ASSERT_EQ(cpu.memory[HL_test_register], 21);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}   
TEST(increment_memory_2, ExampleTest){
    CPU cpu = {0};
    uint16_t HL_test_register = 65355;
    cpu.memory[HL_test_register] = 255;
    increment_memory(&cpu, HL_test_register);
    ASSERT_EQ(cpu.memory[HL_test_register], 0);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 1);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
}   
    
TEST(decrement_register_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.C = 0;
    decrement_register(&cpu, &cpu.registers.C);
    ASSERT_EQ(cpu.registers.C, 255);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
}   

TEST(decrement_register_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.C = 100;
    decrement_register(&cpu, &cpu.registers.C);
    ASSERT_EQ(cpu.registers.C, 99);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 0);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(increment_register_pair_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 10;
    cpu.registers.C = 50;
    increment_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 10);
    ASSERT_EQ(cpu.registers.C, 51);
}

TEST(increment_register_pair_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 10;
    cpu.registers.C = 0xFF;
    increment_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 11);
    ASSERT_EQ(cpu.registers.C, 0);
}
 
TEST(increment_register_pair_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0xFF;
    cpu.registers.C = 0xFF;
    increment_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 0);
    ASSERT_EQ(cpu.registers.C, 0);
}

TEST(increment_register_pair_4, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0xFF;
    cpu.registers.C = 0;
    increment_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 0xFF);
    ASSERT_EQ(cpu.registers.C, 1);
}

TEST(decrement_register_pair_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 10;
    cpu.registers.C = 50;
    decrement_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 10);
    ASSERT_EQ(cpu.registers.C, 49);
}

TEST(decrement_register_pair_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 10;
    cpu.registers.C = 0xFF;
    decrement_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 0xA);
    ASSERT_EQ(cpu.registers.C, 0xFE);
}
 
TEST(decrement_register_pair_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0xFF;
    cpu.registers.C = 0xFF;
    increment_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 0);
    ASSERT_EQ(cpu.registers.C, 0);
}

TEST(decrement_register_pair_4, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0xFF;
    cpu.registers.C = 0;
    increment_register_pair(&cpu.registers.B,&cpu.registers.C);
    ASSERT_EQ(cpu.registers.B, 0xFF);
    ASSERT_EQ(cpu.registers.C, 1);
}
 
TEST(add_register_pair_HL_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0x05;
    cpu.registers.C = 0x10;
    cpu.registers.H = 0x01;
    cpu.registers.L = 0x01;
    add_reg_pair_to_HL(&cpu, &cpu.registers.B, &cpu.registers.C);
    uint16_t result = (cpu.registers.H << 8) | cpu.registers.L;
    ASSERT_EQ(result, 1553);
    ASSERT_EQ(cpu.flags.C, 0);
}

TEST(add_register_pair_HL_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0xFF;
    cpu.registers.C = 0xFF;
    cpu.registers.H = 0xFF;
    cpu.registers.L = 0xFF;
    add_reg_pair_to_HL(&cpu, &cpu.registers.B, &cpu.registers.C);
    uint16_t result = (cpu.registers.H << 8) | cpu.registers.L;
    ASSERT_EQ(result, 65534);
    ASSERT_EQ(cpu.flags.C, 1);
}
 
TEST(add_register_pair_HL_3, ExampleTest){
    CPU cpu = {0};
    cpu.registers.B = 0xFF;
    cpu.registers.C = 0xFF;
    cpu.registers.H = 0x0;
    cpu.registers.L = 0x0;
    add_reg_pair_to_HL(&cpu, &cpu.registers.B, &cpu.registers.C);
    uint16_t result = (cpu.registers.H << 8) | cpu.registers.L;
    ASSERT_EQ(result, 0xFFFF);
    ASSERT_EQ(cpu.flags.C, 0);
}     

//@@@TODO: I am not sure how happy I am for these testing the DAA correctly so I need to come
//back and sort this out

TEST(decimal_adjust_accumulator_1, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 200; //0b11001000
    decimal_adjust_accumulator(&cpu);
    //not greater than 9 4 bits 
    //AC flag not set either so step one skipped
    //0b1100 -> greater than 9 so add 6
    //but that gives 0b10010 and 1 is carried so 0b0010
    //combined we are left with 0b00101000(40)
    ASSERT_EQ(cpu.registers.A, 40);
    ASSERT_EQ(cpu.flags.C, 1);
}

TEST(decimal_adjust_accumulator_2, ExampleTest){
    CPU cpu = {0};
    cpu.registers.A = 255; //0b11111111
    decimal_adjust_accumulator(&cpu);
    //step 1 =  0b00000101
    //step 2 = 0b0110 0101
    ASSERT_EQ(cpu.registers.A, 101);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(decimal_adjust_accumulator_3, ExampleTest) {
    CPU cpu = {0};
    cpu.registers.A = 0x23;
    decimal_adjust_accumulator(&cpu);
    ASSERT_EQ(cpu.registers.A, 0x23);
    ASSERT_EQ(cpu.flags.C, 0);
}

TEST(decimal_adjust_accumulator_4, ExampleTest) {
    CPU cpu = {0};
    cpu.registers.A = 0x19;
    decimal_adjust_accumulator(&cpu);
    ASSERT_EQ(cpu.registers.A, 0x19);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(decimal_adjust_accumulator_5, Nochanges) {
    CPU cpu = {0};
    cpu.registers.A = 0x91;
    decimal_adjust_accumulator(&cpu);
    ASSERT_EQ(cpu.registers.A, 0x91);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(decimal_adjust_accumulator_6, AccumulatorIs0xFF) {
    CPU cpu = {0};
    cpu.registers.A = 0xFF;
    decimal_adjust_accumulator(&cpu);
    ASSERT_EQ(cpu.registers.A, 0x65);
    ASSERT_EQ(cpu.flags.C, 1);
}

TEST(decimal_adjust_accumulator_7, ResultZeroAfterAdjustment) {
    CPU cpu = {0};
    cpu.registers.A = 0x90; //0b10010000
    decimal_adjust_accumulator(&cpu);
    //step one ignored, too low
    //step two ignored too because its =9
    ASSERT_EQ(cpu.registers.A, 0x90);
    ASSERT_EQ(cpu.flags.C, 0);
    ASSERT_EQ(cpu.flags.AC, 0);
}

TEST(decimal_adjust_accumulator_8, JustBelowAdjustmentThreshold) {
    CPU cpu = {0};
    cpu.registers.A = 0x08;
    decimal_adjust_accumulator(&cpu);
    ASSERT_EQ(cpu.registers.A, 0x08);
    ASSERT_EQ(cpu.flags.C, 0);
}

TEST(decimal_adjust_accumulator_9, OnlyTopBytes) {
    CPU cpu = {0};
    cpu.registers.A = 0xA0;
    decimal_adjust_accumulator(&cpu);
    ASSERT_EQ(cpu.registers.A, 0x00);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
}
