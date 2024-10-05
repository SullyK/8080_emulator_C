#include "../src/branch.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(add_two, test_1) {
  int x = 1;
  int y = 2;
  int z = add_two(x, y);
  ASSERT_EQ(z, 3);
}

TEST(jump_addr, test1) {
  CPU cpu = {0};
  cpu.PC = 4000;
  uint8_t byte_two = 0xAA;
  uint8_t byte_three = 0xAA;
  jmp_addr(&cpu, byte_three, byte_two);
  ASSERT_EQ(cpu.PC, 0xAAAA);
}

TEST(jump_addr, test2) {
  CPU cpu = {0};
  cpu.PC = 4000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  jmp_addr(&cpu, byte_three, byte_two);
  ASSERT_EQ(cpu.PC, 0xFFFF);
}

TEST(conditionalJump, NZJumpZ1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.Z = 1;
  conditional_jump(&cpu, byte_three, byte_two, 0);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(conditional_jump, NZJumpZ0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.Z = 0;
  conditional_jump(&cpu, byte_three, byte_two, 0);
  ASSERT_EQ(cpu.PC, 0xFFFF);
}

TEST(conditionalJump, ZJumpZ1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.Z = 1;
  conditional_jump(&cpu, byte_three, byte_two, 1);
  ASSERT_EQ(cpu.PC, 0xFFFF);
}

TEST(conditional_jump, ZJumpZ0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.Z = 0;
  conditional_jump(&cpu, byte_three, byte_two, 1);
  ASSERT_EQ(cpu.PC, 0x1000);
}

TEST(conditionalJump, NCJumpC1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.C = 1;
  conditional_jump(&cpu, byte_three, byte_two, 2);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(conditional_jump, NCJumpC0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.C = 0;
  conditional_jump(&cpu, byte_three, byte_two, 2);
  ASSERT_EQ(cpu.PC, 0xFFFF);
}

TEST(conditionalJump, CJumpC1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xAF;
  uint8_t byte_three = 0xFF;
  cpu.flags.C = 1;
  conditional_jump(&cpu, byte_three, byte_two, 3);
  ASSERT_EQ(cpu.PC, 0xFFAF);
}

TEST(conditional_jump, CJumpC0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.C = 0;
  conditional_jump(&cpu, byte_three, byte_two, 3);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(conditionalJump, POJumpP1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.P = 1;
  conditional_jump(&cpu, byte_three, byte_two, 4);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(conditional_jump, POJumpP0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.P = 0;
  conditional_jump(&cpu, byte_three, byte_two, 4);
  ASSERT_EQ(cpu.PC, 0xFFFF);
}

TEST(conditionalJump, PEJumpP1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xAF;
  uint8_t byte_three = 0xFF;
  cpu.flags.P = 1;
  conditional_jump(&cpu, byte_three, byte_two, 5);
  ASSERT_EQ(cpu.PC, 0xFFAF);
}

TEST(conditional_jump, PEJumpP0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.C = 0;
  conditional_jump(&cpu, byte_three, byte_two, 5);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(conditionalJump, PJumpS1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.S = 1;
  conditional_jump(&cpu, byte_three, byte_two, 6);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(conditional_jump, PJumpS0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.S = 0;
  conditional_jump(&cpu, byte_three, byte_two, 6);
  ASSERT_EQ(cpu.PC, 0xFFFF);
}

TEST(conditionalJump, MJumpS1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xAF;
  uint8_t byte_three = 0xFF;
  cpu.flags.S = 1;
  conditional_jump(&cpu, byte_three, byte_two, 7);
  ASSERT_EQ(cpu.PC, 0xFFAF);
}

TEST(conditional_jump, MJumpS0) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.S = 0;
  conditional_jump(&cpu, byte_three, byte_two, 7);
  ASSERT_EQ(cpu.PC, 1000);
}

TEST(call_addr, test1) {
  CPU cpu = {0};
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  call_addr(&cpu, byte_two, byte_three);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_PC(cpu.PC, 0x7ACC);
}

TEST(conditional_call, NZJmpZ1) {
  CPU cpu = {0};
  cpu.flags.Z = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 0);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_PC(cpu.PC, 0x0402);
}

TEST(conditional_call, NZJmpZ0) {
  CPU cpu = {0};
  cpu.flags.Z = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 0);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_PC(cpu.PC, 0x7ACC);
}

TEST(conditional_call, ZJmpZ1) {
  CPU cpu = {0};
  cpu.flags.Z = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 1);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_PC(cpu.PC, 0x7ACC);
}

TEST(conditional_call, ZJmpZ0) {
  CPU cpu = {0};
  cpu.flags.Z = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 1);

  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_PC(cpu.PC, 0x0402);
}

//-------
 
TEST(conditional_call, NCJmpC1) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 2);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_PC(cpu.PC, 0x0402);
}

TEST(conditional_call, NCJmpC0) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 2);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_PC(cpu.PC, 0x7ACC);
}

TEST(conditional_call, CjmpC1) {
  CPU cpu = {0};
  cpu.flags.Z = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 3);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_PC(cpu.PC, 0x7ACC);
}

TEST(conditional_call, CJmpC0) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[SP - 1] = 0xAA; // 999
  cpu.memory[SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_two, byte_three, 3);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_PC(cpu.PC, 0x0402);
}

 
 //-------
  
 TEST(conditional_call, POJmpP1) {
   CPU cpu = {0};
   cpu.flags.P = 1;
   cpu.SP = 1000;
   cpu.PC = 0x0402;
   cpu.memory[SP - 1] = 0xAA; // 999
   cpu.memory[SP - 2] = 0xBB; // 998
   uint8_t byte_two = 0xCC;
   uint8_t byte_three = 0x7A;
   conditional_call(&cpu, byte_two, byte_three, 4);
   ASSERT_EQ(cpu.memory[999], 0xAA);
   ASSERT_EQ(cpu.memory[998], 0xBB);
   ASSERT_EQ(cpu.SP, 1000);
   ASSERT_PC(cpu.PC, 0x0402);
 }

 TEST(conditional_call, POJmpP0) {
   CPU cpu = {0};
   cpu.flags.P = 0;
   cpu.SP = 1000;
   cpu.PC = 0x0402;
   cpu.memory[SP - 1] = 0xAA; // 999
   cpu.memory[SP - 2] = 0xBB; // 998
   uint8_t byte_two = 0xCC;
   uint8_t byte_three = 0x7A;
   conditional_call(&cpu, byte_two, byte_three, 4);
   ASSERT_EQ(cpu.memory[999], 0x04);
   ASSERT_EQ(cpu.memory[998], 0x02);
   ASSERT_EQ(cpu.SP, 998);
   ASSERT_PC(cpu.PC, 0x7ACC);
 }

 TEST(conditional_call, PEjmpP1) {
   CPU cpu = {0};
   cpu.flags.P = 1;
   cpu.SP = 1000;
   cpu.PC = 0x0402;
   cpu.memory[SP - 1] = 0xAA; // 999
   cpu.memory[SP - 2] = 0xBB; // 998
   uint8_t byte_two = 0xCC;
   uint8_t byte_three = 0x7A;
   conditional_call(&cpu, byte_two, byte_three, 5);
   ASSERT_EQ(cpu.memory[999], 0x04);
   ASSERT_EQ(cpu.memory[998], 0x02);
   ASSERT_EQ(cpu.SP, 998);
   ASSERT_PC(cpu.PC, 0x7ACC);
 }

TEST(conditional_call, PEJmpP0) {
    CPU cpu = {0};
    cpu.flags.P = 0;
    cpu.SP = 1000;
    cpu.PC = 0x0402;
    cpu.memory[SP - 1] = 0xAA; // 999
    cpu.memory[SP - 2] = 0xBB; // 998
    uint8_t byte_two = 0xCC;
    uint8_t byte_three = 0x7A;
    conditional_call(&cpu, byte_two, byte_three, 5);
   ASSERT_EQ(cpu.memory[999], 0xAA);
   ASSERT_EQ(cpu.memory[998], 0xBB);
   ASSERT_EQ(cpu.SP, 1000);
   ASSERT_PC(cpu.PC, 0x0402);
 }

 
 
 //-------
  
 TEST(conditional_call, PJmpS1) {
   CPU cpu = {0};
   cpu.flags.S = 1;
   cpu.SP = 1000;
   cpu.PC = 0x0402;
   cpu.memory[SP - 1] = 0xAA; // 999
   cpu.memory[SP - 2] = 0xBB; // 998
   uint8_t byte_two = 0xCC;
   uint8_t byte_three = 0x7A;
   conditional_call(&cpu, byte_two, byte_three, 6);
   ASSERT_EQ(cpu.memory[999], 0xAA);
   ASSERT_EQ(cpu.memory[998], 0xBB);
   ASSERT_EQ(cpu.SP, 1000);
   ASSERT_PC(cpu.PC, 0x0402);
 }

 TEST(conditional_call, PJmpS0) {
   CPU cpu = {0};
   cpu.flags.S = 0;
   cpu.SP = 1000;
   cpu.PC = 0x0402;
   cpu.memory[SP - 1] = 0xAA; // 999
   cpu.memory[SP - 2] = 0xBB; // 998
   uint8_t byte_two = 0xCC;
   uint8_t byte_three = 0x7A;
   conditional_call(&cpu, byte_two, byte_three, 6);
   ASSERT_EQ(cpu.memory[999], 0x04);
   ASSERT_EQ(cpu.memory[998], 0x02);
   ASSERT_EQ(cpu.SP, 998);
   ASSERT_PC(cpu.PC, 0x7ACC);
 }

 TEST(conditional_call, MjmpS1) {
   CPU cpu = {0};
   cpu.flags.S = 1;
   cpu.SP = 1000;
   cpu.PC = 0x0402;
   cpu.memory[SP - 1] = 0xAA; // 999
   cpu.memory[SP - 2] = 0xBB; // 998
   uint8_t byte_two = 0xCC;
   uint8_t byte_three = 0x7A;
   conditional_call(&cpu, byte_two, byte_three, 7);
   ASSERT_EQ(cpu.memory[999], 0x04);
   ASSERT_EQ(cpu.memory[998], 0x02);
   ASSERT_EQ(cpu.SP, 998);
   ASSERT_PC(cpu.PC, 0x7ACC);
 }

TEST(conditional_call, MJmpS0) {
    CPU cpu = {0};
    cpu.flags.S = 0;
    cpu.SP = 1000;
    cpu.PC = 0x0402;
    cpu.memory[SP - 1] = 0xAA; // 999
    cpu.memory[SP - 2] = 0xBB; // 998
    uint8_t byte_two = 0xCC;
    uint8_t byte_three = 0x7A;
    conditional_call(&cpu, byte_two, byte_three, 7);
   ASSERT_EQ(cpu.memory[999], 0xAA);
   ASSERT_EQ(cpu.memory[998], 0xBB);
   ASSERT_EQ(cpu.SP, 1000);
   ASSERT_PC(cpu.PC, 0x0402);
 }

  
