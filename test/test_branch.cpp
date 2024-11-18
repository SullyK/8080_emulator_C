#include "../src/branch.h"
#include <gtest/gtest.h>
#include <iostream>

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
  ASSERT_EQ(cpu.PC, 1003);
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
  ASSERT_EQ(cpu.PC, 1003);
}

TEST(conditionalJump, NCJumpC1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.C = 1;
  conditional_jump(&cpu, byte_three, byte_two, 2);
  ASSERT_EQ(cpu.PC, 1003);
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
  ASSERT_EQ(cpu.PC, 1003);
}

TEST(conditionalJump, POJumpP1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.P = 1;
  conditional_jump(&cpu, byte_three, byte_two, 4);
  ASSERT_EQ(cpu.PC, 1003);
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
  ASSERT_EQ(cpu.PC, 1003);
}

TEST(conditionalJump, PJumpS1) {
  CPU cpu = {0};
  cpu.PC = 1000;
  uint8_t byte_two = 0xFF;
  uint8_t byte_three = 0xFF;
  cpu.flags.S = 1;
  conditional_jump(&cpu, byte_three, byte_two, 6);
  ASSERT_EQ(cpu.PC, 1003);
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
  ASSERT_EQ(cpu.PC, 1003);
}

TEST(call_addr, test1) {
  CPU cpu = {0};
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; 
  cpu.memory[cpu.SP - 2] = 0xBB; 
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  call_addr(&cpu, byte_three, byte_two);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, NZJmpZ1) {
  CPU cpu = {0};
  cpu.flags.Z = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 0);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

TEST(conditional_call, NZJmpZ0) {
  CPU cpu = {0};
  cpu.flags.Z = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 0);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, ZJmpZ1) {
  CPU cpu = {0};
  cpu.flags.Z = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 1);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, ZJmpZ0) {
  CPU cpu = {0};
  cpu.flags.Z = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 1);

  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

//-------

TEST(conditional_call, NCJmpC1) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 2);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

TEST(conditional_call, NCJmpC0) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 2);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, CjmpC1) {
  CPU cpu = {0};
  cpu.flags.C = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 3);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, CJmpC0) {
  CPU cpu = {0};
  cpu.flags.C = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 3);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

//-------

TEST(conditional_call, POJmpP1) {
  CPU cpu = {0};
  cpu.flags.P = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 4);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

TEST(conditional_call, POJmpP0) {
  CPU cpu = {0};
  cpu.flags.P = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 4);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, PEjmpP1) {
  CPU cpu = {0};
  cpu.flags.P = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 5);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, PEJmpP0) {
  CPU cpu = {0};
  cpu.flags.P = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 5);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

//-------

TEST(conditional_call, PJmpS1) {
  CPU cpu = {0};
  cpu.flags.S = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 6);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

TEST(conditional_call, PJmpS0) {
  CPU cpu = {0};
  cpu.flags.S = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 6);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, MjmpS1) {
  CPU cpu = {0};
  cpu.flags.S = 1;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 7);
  ASSERT_EQ(cpu.memory[999], 0x04);
  ASSERT_EQ(cpu.memory[998], 0x02);
  ASSERT_EQ(cpu.SP, 998);
  ASSERT_EQ(cpu.PC, 0x7ACC);
}

TEST(conditional_call, MJmpS0) {
  CPU cpu = {0};
  cpu.flags.S = 0;
  cpu.SP = 1000;
  cpu.PC = 0x0402;
  cpu.memory[cpu.SP - 1] = 0xAA; // 999
  cpu.memory[cpu.SP - 2] = 0xBB; // 998
  uint8_t byte_two = 0xCC;
  uint8_t byte_three = 0x7A;
  conditional_call(&cpu, byte_three, byte_two, 7);
  ASSERT_EQ(cpu.memory[999], 0xAA);
  ASSERT_EQ(cpu.memory[998], 0xBB);
  ASSERT_EQ(cpu.SP, 1000);
  ASSERT_EQ(cpu.PC, 0x0405);
}

TEST(branch_return, test1) {
  CPU cpu = {0};
  cpu.SP = 1000;
  cpu.memory[cpu.SP] = 0xAF;
  cpu.memory[cpu.SP + 1] = 0x22;
  cpu.PC = 0xFFFF;
  branch_return(&cpu);
  ASSERT_EQ(cpu.PC, 0x22AF);
  ASSERT_EQ(cpu.SP, 1002);
}

struct ConditionalBranchTestParams {

  uint8_t Z_value;
  uint8_t C_value;
  uint8_t P_value;
  uint8_t S_value;

  uint16_t SP_value;
  uint16_t PC_value;
  uint8_t memory_1;
  uint8_t memory_2;

  uint16_t PC_assert_value;
  uint16_t SP_assert_value;
  uint8_t condition;
};

class ConditionalBranchReturnTests
    : public ::testing::TestWithParam<ConditionalBranchTestParams> {
protected:
  CPU cpu;

  void SetUp() override {
    cpu = {0};

    auto param = GetParam();
    cpu.memory[param.SP_value] = param.memory_1;
    cpu.memory[param.SP_value + 1] = param.memory_2;
    cpu.flags.S = param.S_value;
    cpu.flags.Z = param.Z_value;
    cpu.flags.P = param.P_value;
    cpu.flags.C = param.C_value;
    cpu.SP = param.SP_value;
    cpu.PC = param.PC_value;
  }
};

TEST_P(ConditionalBranchReturnTests, CheckTheConditionalBranchImplementation) {
  auto param = GetParam();
  conditional_branch_return(&cpu, param.condition);
  ASSERT_EQ(cpu.PC, param.PC_assert_value);
  ASSERT_EQ(cpu.SP, param.SP_assert_value);
}

INSTANTIATE_TEST_SUITE_P(
    ConditionalBranchReturnTestsCases, // Name of the test suite
    ConditionalBranchReturnTests,      // Test suite class
    ::testing::Values(
        // first test - Not zero - z=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 0},
        // below test - Not zero - z=1, condtion not met
        ConditionalBranchTestParams{1, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22, 0xFFFB,
                                    500, 0},
        // below test - zero, - z=0, conditon not met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 1},
        // below test - zero, - z=1, condition met
        ConditionalBranchTestParams{1, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 1},
        // below test - Not carry, - c=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 2},
        // below test - Not carry, c=1, condition notmet
        ConditionalBranchTestParams{0, 1, 0, 1, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 2},
        // below test - carry, c=0, condition notmet
        ConditionalBranchTestParams{0, 0, 0, 1, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 3},
        // below test - carry, c=1, condition met
        ConditionalBranchTestParams{0, 1, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 3},
        // below test - parity odd, p=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 4},
        // below test - parity odd, p=1, condition not met
        ConditionalBranchTestParams{0, 0, 1, 0, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 4},
        // below test - parity even, p=0, condition not met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 5},
        // below test - parity even, p=1, condition met
        ConditionalBranchTestParams{0, 0, 1, 0, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 5},
        // below test - plus , s=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 6},
        // below test - plus, s=1, condition not met
        ConditionalBranchTestParams{0, 0, 0, 1, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 6},
        // below test - minus , s=0, condition not met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFA, 0xAF, 0x22,
        0xFFFB,
                                    500, 7},
        // below test - minus, , s=1, condition met
        ConditionalBranchTestParams{0, 0, 0, 1, 500, 0xFFFA, 0xAF, 0x22,
        0x22AF,
                                    502, 7}));
// above = conditional return
// ----------------------------------------
//

TEST(restart, test1) {
  CPU cpu = {0};
  cpu.SP = 5555;
  cpu.PC = 0xA24F;
  cpu.memory[cpu.SP - 1] = 0xFF;
  cpu.memory[cpu.SP - 2] = 0xFF;
  uint8_t n_value = 2;
  // make sure these above numbers are changed for mem
  restart(&cpu, n_value);
  ASSERT_EQ(cpu.memory[5553], 0x4F);     // low_byte
  ASSERT_EQ(cpu.memory[5553 + 1], 0xA2); // high_byte
  ASSERT_EQ(cpu.SP, 5553);
  ASSERT_EQ(cpu.PC, 16); // 0x10
}

TEST(restart, lowest_sp) {
  CPU cpu = {0};
  cpu.SP = 2;
  cpu.PC = 0x1234;
  cpu.memory[cpu.SP - 1] = 0xff;
  cpu.memory[cpu.SP - 2] = 0xff;
  uint8_t n_value = 7;
  // make sure these above numbers are changed for mem
  restart(&cpu, n_value);
  ASSERT_EQ(cpu.memory[0], 0x34);     // low_byte
  ASSERT_EQ(cpu.memory[0 + 1], 0x12); // high_byte
  ASSERT_EQ(cpu.SP, 0);
  ASSERT_EQ(cpu.PC, (7 * 8)); // *8 for n_value restart
                              // from rsrt instruction
}

TEST(restart, highest_sp) {
  CPU cpu = {0};
  cpu.SP = 0xFFFF;
  cpu.PC = 0xABCD;
  cpu.memory[cpu.SP - 1] = 0xAA;
  cpu.memory[cpu.SP - 2] = 0xBB;
  uint8_t n_value = 6;

  restart(&cpu, n_value);
  ASSERT_EQ(cpu.memory[0xFFFF - 2], 0xCD);
  ASSERT_EQ(cpu.memory[0xFFFF - 1], 0xAB);

  ASSERT_EQ(cpu.SP, 0xFFFF - 2);
  ASSERT_EQ(cpu.PC, (n_value * 8));
}
TEST(PCHL, test1) {
  CPU cpu = {0};
  cpu.PC = 0xFFFF;
  cpu.registers.H = 0xAA; // high byte
  cpu.registers.L = 0xBB; // low byte
  PCHL(&cpu);
  ASSERT_EQ(cpu.PC, 0xAABB);
}
