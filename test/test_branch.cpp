#include "../src/branch.h"
#include <gtest/gtest.h>
#include <iostream>

// TEST(add_two, test_1) {
//   int x = 1;
//   int y = 2;
//   int z = add_two(x, y);
//   ASSERT_EQ(z, 3);
// }
//
// TEST(jump_addr, test1) {
//   CPU cpu = {0};
//   cpu.PC = 4000;
//   uint8_t byte_two = 0xAA;
//   uint8_t byte_three = 0xAA;
//   jmp_addr(&cpu, byte_three, byte_two);
//   ASSERT_EQ(cpu.PC, 0xAAAA);
// }
//
// TEST(jump_addr, test2) {
//   CPU cpu = {0};
//   cpu.PC = 4000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   jmp_addr(&cpu, byte_three, byte_two);
//   ASSERT_EQ(cpu.PC, 0xFFFF);
// }
//
// TEST(conditionalJump, NZJumpZ1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.Z = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 0);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(conditional_jump, NZJumpZ0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.Z = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 0);
//   ASSERT_EQ(cpu.PC, 0xFFFF);
// }
//
// TEST(conditionalJump, ZJumpZ1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.Z = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 1);
//   ASSERT_EQ(cpu.PC, 0xFFFF);
// }
//
// TEST(conditional_jump, ZJumpZ0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.Z = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 1);
//   ASSERT_EQ(cpu.PC, 0x1000);
// }
//
// TEST(conditionalJump, NCJumpC1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.C = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 2);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(conditional_jump, NCJumpC0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.C = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 2);
//   ASSERT_EQ(cpu.PC, 0xFFFF);
// }
//
// TEST(conditionalJump, CJumpC1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xAF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.C = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 3);
//   ASSERT_EQ(cpu.PC, 0xFFAF);
// }
//
// TEST(conditional_jump, CJumpC0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.C = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 3);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(conditionalJump, POJumpP1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.P = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 4);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(conditional_jump, POJumpP0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.P = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 4);
//   ASSERT_EQ(cpu.PC, 0xFFFF);
// }
//
// TEST(conditionalJump, PEJumpP1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xAF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.P = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 5);
//   ASSERT_EQ(cpu.PC, 0xFFAF);
// }
//
// TEST(conditional_jump, PEJumpP0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.C = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 5);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(conditionalJump, PJumpS1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.S = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 6);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(conditional_jump, PJumpS0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.S = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 6);
//   ASSERT_EQ(cpu.PC, 0xFFFF);
// }
//
// TEST(conditionalJump, MJumpS1) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xAF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.S = 1;
//   conditional_jump(&cpu, byte_three, byte_two, 7);
//   ASSERT_EQ(cpu.PC, 0xFFAF);
// }
//
// TEST(conditional_jump, MJumpS0) {
//   CPU cpu = {0};
//   cpu.PC = 1000;
//   uint8_t byte_two = 0xFF;
//   uint8_t byte_three = 0xFF;
//   cpu.flags.S = 0;
//   conditional_jump(&cpu, byte_three, byte_two, 7);
//   ASSERT_EQ(cpu.PC, 1000);
// }
//
// TEST(call_addr, test1) {
//   CPU cpu = {0};
//   cpu.SP = 1000;
//   cpu.PC = 0x0402;
//   cpu.memory[SP - 1] = 0xAA; // 999
//   cpu.memory[SP - 2] = 0xBB; // 998
//   uint8_t byte_two = 0xCC;
//   uint8_t byte_three = 0x7A;
//   call_addr(&cpu, byte_two, byte_three);
//   ASSERT_EQ(cpu.memory[999], 0x04);
//   ASSERT_EQ(cpu.memory[998], 0x02);
//   ASSERT_EQ(cpu.SP, 998);
//   ASSERT_PC(cpu.PC, 0x7ACC);
// }
//
// TEST(conditional_call, NZJmpZ1) {
//   CPU cpu = {0};
//   cpu.flags.Z = 1;
//   cpu.SP = 1000;
//   cpu.PC = 0x0402;
//   cpu.memory[SP - 1] = 0xAA; // 999
//   cpu.memory[SP - 2] = 0xBB; // 998
//   uint8_t byte_two = 0xCC;
//   uint8_t byte_three = 0x7A;
//   conditional_call(&cpu, byte_two, byte_three, 0);
//   ASSERT_EQ(cpu.memory[999], 0xAA);
//   ASSERT_EQ(cpu.memory[998], 0xBB);
//   ASSERT_EQ(cpu.SP, 1000);
//   ASSERT_PC(cpu.PC, 0x0402);
// }
//
// TEST(conditional_call, NZJmpZ0) {
//   CPU cpu = {0};
//   cpu.flags.Z = 0;
//   cpu.SP = 1000;
//   cpu.PC = 0x0402;
//   cpu.memory[SP - 1] = 0xAA; // 999
//   cpu.memory[SP - 2] = 0xBB; // 998
//   uint8_t byte_two = 0xCC;
//   uint8_t byte_three = 0x7A;
//   conditional_call(&cpu, byte_two, byte_three, 0);
//   ASSERT_EQ(cpu.memory[999], 0x04);
//   ASSERT_EQ(cpu.memory[998], 0x02);
//   ASSERT_EQ(cpu.SP, 998);
//   ASSERT_PC(cpu.PC, 0x7ACC);
// }
//
// TEST(conditional_call, ZJmpZ1) {
//   CPU cpu = {0};
//   cpu.flags.Z = 1;
//   cpu.SP = 1000;
//   cpu.PC = 0x0402;
//   cpu.memory[SP - 1] = 0xAA; // 999
//   cpu.memory[SP - 2] = 0xBB; // 998
//   uint8_t byte_two = 0xCC;
//   uint8_t byte_three = 0x7A;
//   conditional_call(&cpu, byte_two, byte_three, 1);
//   ASSERT_EQ(cpu.memory[999], 0x04);
//   ASSERT_EQ(cpu.memory[998], 0x02);
//   ASSERT_EQ(cpu.SP, 998);
//   ASSERT_PC(cpu.PC, 0x7ACC);
// }
//
// TEST(conditional_call, ZJmpZ0) {
//   CPU cpu = {0};
//   cpu.flags.Z = 0;
//   cpu.SP = 1000;
//   cpu.PC = 0x0402;
//   cpu.memory[SP - 1] = 0xAA; // 999
//   cpu.memory[SP - 2] = 0xBB; // 998
//   uint8_t byte_two = 0xCC;
//   uint8_t byte_three = 0x7A;
//   conditional_call(&cpu, byte_two, byte_three, 1);
//
//   ASSERT_EQ(cpu.memory[999], 0xAA);
//   ASSERT_EQ(cpu.memory[998], 0xBB);
//   ASSERT_EQ(cpu.SP, 1000);
//   ASSERT_PC(cpu.PC, 0x0402);
// }
//
////-------
//
// TEST(conditional_call, NCJmpC1) {
//  CPU cpu = {0};
//  cpu.flags.C = 1;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 2);
//  ASSERT_EQ(cpu.memory[999], 0xAA);
//  ASSERT_EQ(cpu.memory[998], 0xBB);
//  ASSERT_EQ(cpu.SP, 1000);
//  ASSERT_PC(cpu.PC, 0x0402);
//}
//
// TEST(conditional_call, NCJmpC0) {
//  CPU cpu = {0};
//  cpu.flags.C = 0;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 2);
//  ASSERT_EQ(cpu.memory[999], 0x04);
//  ASSERT_EQ(cpu.memory[998], 0x02);
//  ASSERT_EQ(cpu.SP, 998);
//  ASSERT_PC(cpu.PC, 0x7ACC);
//}
//
// TEST(conditional_call, CjmpC1) {
//  CPU cpu = {0};
//  cpu.flags.Z = 1;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 3);
//  ASSERT_EQ(cpu.memory[999], 0x04);
//  ASSERT_EQ(cpu.memory[998], 0x02);
//  ASSERT_EQ(cpu.SP, 998);
//  ASSERT_PC(cpu.PC, 0x7ACC);
//}
//
// TEST(conditional_call, CJmpC0) {
//  CPU cpu = {0};
//  cpu.flags.C = 0;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 3);
//  ASSERT_EQ(cpu.memory[999], 0xAA);
//  ASSERT_EQ(cpu.memory[998], 0xBB);
//  ASSERT_EQ(cpu.SP, 1000);
//  ASSERT_PC(cpu.PC, 0x0402);
//}
//
////-------
//
// TEST(conditional_call, POJmpP1) {
//  CPU cpu = {0};
//  cpu.flags.P = 1;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 4);
//  ASSERT_EQ(cpu.memory[999], 0xAA);
//  ASSERT_EQ(cpu.memory[998], 0xBB);
//  ASSERT_EQ(cpu.SP, 1000);
//  ASSERT_PC(cpu.PC, 0x0402);
//}
//
// TEST(conditional_call, POJmpP0) {
//  CPU cpu = {0};
//  cpu.flags.P = 0;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 4);
//  ASSERT_EQ(cpu.memory[999], 0x04);
//  ASSERT_EQ(cpu.memory[998], 0x02);
//  ASSERT_EQ(cpu.SP, 998);
//  ASSERT_PC(cpu.PC, 0x7ACC);
//}
//
// TEST(conditional_call, PEjmpP1) {
//  CPU cpu = {0};
//  cpu.flags.P = 1;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 5);
//  ASSERT_EQ(cpu.memory[999], 0x04);
//  ASSERT_EQ(cpu.memory[998], 0x02);
//  ASSERT_EQ(cpu.SP, 998);
//  ASSERT_PC(cpu.PC, 0x7ACC);
//}
//
// TEST(conditional_call, PEJmpP0) {
//  CPU cpu = {0};
//  cpu.flags.P = 0;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 5);
//  ASSERT_EQ(cpu.memory[999], 0xAA);
//  ASSERT_EQ(cpu.memory[998], 0xBB);
//  ASSERT_EQ(cpu.SP, 1000);
//  ASSERT_PC(cpu.PC, 0x0402);
//}
//
////-------
//
// TEST(conditional_call, PJmpS1) {
//  CPU cpu = {0};
//  cpu.flags.S = 1;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 6);
//  ASSERT_EQ(cpu.memory[999], 0xAA);
//  ASSERT_EQ(cpu.memory[998], 0xBB);
//  ASSERT_EQ(cpu.SP, 1000);
//  ASSERT_PC(cpu.PC, 0x0402);
//}
//
// TEST(conditional_call, PJmpS0) {
//  CPU cpu = {0};
//  cpu.flags.S = 0;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 6);
//  ASSERT_EQ(cpu.memory[999], 0x04);
//  ASSERT_EQ(cpu.memory[998], 0x02);
//  ASSERT_EQ(cpu.SP, 998);
//  ASSERT_PC(cpu.PC, 0x7ACC);
//}
//
// TEST(conditional_call, MjmpS1) {
//  CPU cpu = {0};
//  cpu.flags.S = 1;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 7);
//  ASSERT_EQ(cpu.memory[999], 0x04);
//  ASSERT_EQ(cpu.memory[998], 0x02);
//  ASSERT_EQ(cpu.SP, 998);
//  ASSERT_PC(cpu.PC, 0x7ACC);
//}
//
// TEST(conditional_call, MJmpS0) {
//  CPU cpu = {0};
//  cpu.flags.S = 0;
//  cpu.SP = 1000;
//  cpu.PC = 0x0402;
//  cpu.memory[SP - 1] = 0xAA; // 999
//  cpu.memory[SP - 2] = 0xBB; // 998
//  uint8_t byte_two = 0xCC;
//  uint8_t byte_three = 0x7A;
//  conditional_call(&cpu, byte_two, byte_three, 7);
//  ASSERT_EQ(cpu.memory[999], 0xAA);
//  ASSERT_EQ(cpu.memory[998], 0xBB);
//  ASSERT_EQ(cpu.SP, 1000);
//  ASSERT_EQ(cpu.PC, 0x0402);
//}
//
// TEST(branch_return, test1) {
//  CPU cpu = {0};
//  cpu.SP = 1000;
//  cpu.memory[SP] = 0xAF;
//  cpu.memory[SP + 1] = 0x22;
//  cpu.PC = 0xFFFF;
//  branch_return(&cpu);
//  ASSERT_EQ(cpu.PC, 0x22AF);
//  ASSERT_EQ(cpu.SP, 1002);
//}
//
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
        ConditionalBranchTestParams{1, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 0},
        // below test - zero, - z=0, conditon not met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 1},
        // below test - zero, - z=1, condition met
        ConditionalBranchTestParams{1, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 1},
        // below test - Not carry, - c=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 2},
        // below test - Not carry, c=1, condition notmet
        ConditionalBranchTestParams{0, 1, 0, 1, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 2},
        // below test - carry, c=0, condition notmet
        ConditionalBranchTestParams{0, 0, 0, 1, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 3},
        // below test - carry, c=1, condition met
        ConditionalBranchTestParams{0, 1, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 3},
        // below test - parity odd, p=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 4},
        // below test - parity odd, p=1, condition not met
        ConditionalBranchTestParams{0, 0, 1, 0, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 4},
        // below test - parity even, p=0, condition not met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 5},
        // below test - parity even, p=1, condition met
        ConditionalBranchTestParams{0, 0, 1, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 5},
        // below test - plus , s=0, condition met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 6},
        // below test - plus, s=1, condition not met
        ConditionalBranchTestParams{0, 0, 0, 1, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 6},
        // below test - minus , s=0, condition not met
        ConditionalBranchTestParams{0, 0, 0, 0, 500, 0xFFFF, 0xAF, 0x22, 0xFFFF,
                                    500, 7},
        // below test - minus, , s=1, condition met
        ConditionalBranchTestParams{0, 0, 0, 1, 500, 0xFFFF, 0xAF, 0x22, 0x22AF,
                                    502, 7}));
