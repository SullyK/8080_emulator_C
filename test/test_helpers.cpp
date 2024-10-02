#include "../src/helpers.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(combine_registers, test_1) {
  CPU cpu = {0};
  uint8_t high = 0b10001000;
  uint8_t low = 0b11111111;
  uint16_t combined = combine_registers(high, low);
  ASSERT_EQ(combined, 0b1000100011111111);
}
