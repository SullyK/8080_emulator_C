#include "../src/io.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(push_rp, test1) {
  CPU cpu = {0};
  cpu.SP = 100;
  uint16_t rp = 0xAA05;
  push_rp(&cpu, rp);
  ASSERT_EQ(cpu.SP, 98);
  ASSERT_EQ(cpu.memory[99], 0xAA);
  ASSERT_EQ(cpu.memory[98], 0x05);
}

TEST(push_psw, test1) {
  CPU cpu = {0};
  CPU *p = &cpu;
  cpu.SP = 30;
  cpu.flags.S = 1;
  cpu.flags.Z = 1;
  cpu.flags.P = 1;
  cpu.flags.C = 1;
  cpu.flags.AC = 1;
  cpu.registers.A = 111;
  push_psw(p);
  ASSERT_EQ(cpu.SP, 28);
  ASSERT_EQ(cpu.memory[29], 111);
  ASSERT_EQ(cpu.memory[28], 0b11010111);
}

 
TEST(push_psw, test2) {
  CPU cpu = {0};
  CPU *p = &cpu;
  cpu.SP = 2;
  cpu.flags.S = 0;
  cpu.flags.Z = 1;
  cpu.flags.P = 0;
  cpu.flags.C = 1;
  cpu.flags.AC = 0;
  cpu.registers.A = 255;
  push_psw(p);
  ASSERT_EQ(cpu.SP, 0);
  ASSERT_EQ(cpu.memory[1], 255);
  ASSERT_EQ(cpu.memory[0], 0b01000011);
}                    

TEST(pop_rp, test1) {
  CPU cpu = {0};
  cpu.SP = 998;
  uint16_t rp = 0xFFFF;
  cpu.memory[998] = 0xBB;
  cpu.memory[999] = 0xAA;
  pop_rp(&cpu, &rp);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(rp, 0xAABB);
}

TEST(pop_rp, test2) {
  CPU cpu = {0};
  cpu.SP = 0;
  uint16_t rp = 0xFFFF;
  cpu.memory[0] = 0x9;
  cpu.memory[1] = 0xA0;
  pop_rp(&cpu, &rp);
  ASSERT_EQ(cpu.SP, 2);
  ASSERT_EQ(rp, 0xA009);
}

TEST(pop_psw, test1){
    CPU cpu = {0};
    cpu.SP = 100;
    cpu.memory[100] = 0b11010111;
    cpu.memory[101] = 222;
    pop_psw(&cpu);
    ASSERT_EQ(cpu.SP, 102);
    ASSERT_EQ(cpu.registers.A, 222);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 1);
    ASSERT_EQ(cpu.flags.Z, 1);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
}

 
TEST(pop_psw, test2){
    CPU cpu = {0};
    cpu.SP = 100;
    cpu.memory[100] = 0b01010111;
    cpu.memory[101] = 0xB6;
    pop_psw(&cpu);
    ASSERT_EQ(cpu.SP, 102);
    ASSERT_EQ(cpu.registers.A, 0xB6);
    ASSERT_EQ(cpu.flags.C, 1);
    ASSERT_EQ(cpu.flags.S, 0);
    ASSERT_EQ(cpu.flags.Z, 1);
    ASSERT_EQ(cpu.flags.P, 1);
    ASSERT_EQ(cpu.flags.AC, 1);
}
