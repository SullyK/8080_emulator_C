#include "../src/branch.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(add_two, test_1) {
  int x = 1;
  int y = 2;
  int z = add_two(x, y);
  ASSERT_EQ(z, 3);
}

TEST(jump_addr, test_1) {
  CPU cpu = {0};
  cpu.PC = 4000;
  uint8_t byte_two = 0xAA;
  uint8_t byte_three = 0xAA;
  jmp_addr(&cpu, byte_three, byte_two);
  ASSERT_EQ(cpu.PC, 0xAAAA);
}
