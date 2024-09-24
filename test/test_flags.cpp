#include "../src/flags.h"
#include <gtest/gtest.h>
#include <iostream>

//@@@ TODO: change where I place these below tests, just need to check they work

// underflow test with carry
TEST(UnderflowTest_with_carry_1, ExampleTest) {
  uint8_t a = 1;
  uint8_t b = 2;
  uint8_t c = 0;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 1); // underflow occurs
}

TEST(UnderflowTest_with_carry_2, ExampleTest) {
  uint8_t a = 1;
  uint8_t b = 0;
  uint8_t c = 1;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

TEST(UnderflowTest_with_carry_3, ExampleTest) {
  uint8_t a = 1;
  uint8_t b = 10;
  uint8_t c = 1;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 1); // underflow occurs
}

TEST(UnderflowTest_with_carry_4, ExampleTest) {
  uint8_t a = 1;
  uint8_t b = 2;
  uint8_t c = 1;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 1);
}

TEST(UnderflowTest_with_carry_5, ExampleTest) {
  uint8_t a = 4;
  uint8_t b = 2;
  uint8_t c = 1;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

TEST(UnderflowTest_with_carry_6, ExampleTest) {
  uint8_t a = 255;
  uint8_t b = 255;
  uint8_t c = 0;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

TEST(UnderflowTest_with_carry_7, ExampleTest) {
  uint8_t a = 0;
  uint8_t b = 0;
  uint8_t c = 1;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 1);
}

TEST(UnderflowTest_with_carry_8, ExampleTest) {
  uint8_t a = 0;
  uint8_t b = 0;
  uint8_t c = 0;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

TEST(UnderflowTest_with_carry_9, ExampleTest) {
  uint8_t a = 250;
  uint8_t b = 5;
  uint8_t c = 0;
  uint8_t result = unsigned_subtract_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

//@@@ TODO: C will always be 1 or 0 in these functions since its 1 bit int
TEST(overflow_addtion_carry_check_with_carry_1, ExampleTest) {
  uint8_t a = 254;
  uint8_t b = 1;
  uint8_t c = 1;
  uint8_t result = unsigned_addition_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 1);
}

TEST(overflow_addtion_carry_check_with_carry_2, ExampleTest) {
  uint8_t a = 254;
  uint8_t b = 1;
  uint8_t c = 0;
  uint8_t result = unsigned_addition_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

TEST(overflow_addtion_carry_check_with_carry_3, ExampleTest) {
  uint8_t a = 4;
  uint8_t b = 250;
  uint8_t c = 1;
  uint8_t result = unsigned_addition_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

TEST(overflow_addtion_carry_check_with_carry_4, ExampleTest) {
  uint8_t a = 3;
  uint8_t b = 250;
  uint8_t c = 1;
  uint8_t result = unsigned_addition_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 0);
}

//@@@ TODO: Is this test correct
TEST(overflow_addtion_carry_check_with_carry_5, ExampleTest) {
  uint8_t a = 255;
  uint8_t b = 255;
  uint8_t c = 1;
  uint8_t result = unsigned_addition_carry_check_with_carry(a, b, c);
  ASSERT_EQ(result, 1);
}

TEST(overflow_4bit_1, ExampleTest) {
  uint8_t a = 10;
  uint8_t b = 6;
  uint8_t result = unsigned_addition_carry_check_4_bit(a, b);
  ASSERT_EQ(result, 1);
}

TEST(overflow_4bit_2, ExampleTest) {
  uint8_t a = 10;
  uint8_t b = 5;
  uint8_t result = unsigned_addition_carry_check_4_bit(a, b);
  ASSERT_EQ(result, 0);
}

TEST(overflow_4bit_3, ExampleTest) {
  uint8_t a = 6;
  uint8_t b = 10;
  uint8_t result = unsigned_addition_carry_check_4_bit(a, b);
  ASSERT_EQ(result, 1);
}

TEST(overflow_4bit_4, ExampleTest) {
  uint8_t a = 0;
  uint8_t b = 31; // this should be seen as 1(4bit), but adding just cause
  uint8_t result = unsigned_addition_carry_check_4_bit(a, b);
  ASSERT_EQ(result, 0);
}

TEST(overflow_4bit_5, ExampleTest) {
  uint8_t a = 5;
  uint8_t b = 5;
  uint8_t result = unsigned_addition_carry_check_4_bit(a, b);
  ASSERT_EQ(result, 0);
}

TEST(overflow_16bit_1, ExampleTest) {
  uint16_t a = 150;
  uint16_t b = 65535;
  uint8_t result = unsigned_addition_carry_check_16_bit(a, b);
  ASSERT_EQ(result, 1);
}

TEST(overflow_16bit_2, ExampleTest) {
  uint16_t a = 150;
  uint16_t b = 65535;
  uint8_t result = unsigned_addition_carry_check_16_bit(b, a);
  ASSERT_EQ(result, 1);
}

TEST(overflow_16bit_3, ExampleTest) {
  uint16_t a = 0;
  uint16_t b = 65535;
  uint8_t result = unsigned_addition_carry_check_16_bit(a, b);
  ASSERT_EQ(result, 0);
}

TEST(overflow_16bit_4, ExampleTest) {
  uint16_t a = 65535;
  uint16_t b = 65535;
  uint8_t result = unsigned_addition_carry_check_16_bit(a, b);
  ASSERT_EQ(result, 1);
}

TEST(overflow_16bit_5, ExampleTest) {
  uint16_t a = 6550;
  uint16_t b = 25535;
  uint8_t result = unsigned_addition_carry_check_16_bit(a, b);
  ASSERT_EQ(result, 0);
}

// overflow tests

TEST(OverflowTest_1, ExampleTest) {
  uint8_t a = 23;
  uint8_t b = 33;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(OverflowTest_2, ExampleTest) {
  uint8_t a = 255;
  uint8_t b = 1;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 1);
}

TEST(OverflowTest_3, ExampleTest) {
  uint8_t a = 255;
  uint8_t b = 0;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(OverflowTest_4, ExampleTest) {
  uint8_t a = 127;
  uint8_t b = 128;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(OverflowTest_5, ExampleTest) {
  uint8_t a = 128;
  uint8_t b = 127;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(OverflowTest_6, ExampleTest) {
  uint8_t a = 128;
  uint8_t b = 128;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 1);
}

TEST(OverflowTest_7, ExampleTest) {
  uint8_t a = 2;
  uint8_t b = 254;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 1);
}

TEST(OverflowTest_8, ExampleTest) {
  uint8_t a = 0;
  uint8_t b = 0;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(OverflowTest_9, ExampleTest) {
  uint8_t a = 255;
  uint8_t b = 0;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(OverflowTest_10, ExampleTest) {
  uint8_t a = 250;
  uint8_t b = 5;
  uint8_t result = unsigned_addition_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

// underflow test
TEST(UnderflowTest_1, ExampleTest) {
  uint8_t a = 1;
  uint8_t b = 2;
  uint8_t result = unsigned_subtract_carry_check(a, b);
  ASSERT_EQ(result, 1);
}

TEST(UnderflowTest_2, ExampleTest) {
  uint8_t a = 2;
  uint8_t b = 1;
  uint8_t result = unsigned_subtract_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(UnderflowTest_3, ExampleTest) {
  uint8_t a = 255;
  uint8_t b = 1;
  uint8_t result = unsigned_subtract_carry_check(a, b);
  ASSERT_EQ(result, 0);
}

TEST(UnderflowTest_4, ExampleTest) {
  uint8_t a = 1;
  uint8_t b = 255;
  uint8_t result = unsigned_subtract_carry_check(a, b);
  ASSERT_EQ(result, 1);
}

// signed tests
TEST(CheckSignedTest_1, ExampleTest) {
  uint8_t number = 0b10000000;
  uint8_t result = check_signed_bit(number);
  ASSERT_EQ(result, 1);
}

TEST(CheckSignedTest_2, ExampleTest) {
  uint8_t number = 0b00000000;
  uint8_t result = check_signed_bit(number);
  ASSERT_EQ(result, 0);
}

TEST(CheckSignedTest_3, ExampleTest) {
  uint8_t number = 0b00000001;
  uint8_t result = check_signed_bit(number);
  ASSERT_EQ(result, 0);
}

TEST(CheckSignedTest_4, ExampleTest) {
  uint8_t number = 0b11111110;
  uint8_t result = check_signed_bit(number);
  ASSERT_EQ(result, 1);
}

// parity tests
TEST(ParityTest_1, ExampleTest) {
  uint8_t number = 0b10101010;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_2, ExampleTest) {
  uint8_t number = 0b00001111;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_3, ExampleTest) {
  uint8_t number = 0b11110000;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_4, ExampleTest) {
  uint8_t number = 0b01010101;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_5, ExampleTest) {
  uint8_t number = 0b011110001;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 0);
}

TEST(ParityTest_6, ExampleTest) {
  uint8_t number = 0b011110111;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 0);
}

TEST(ParityTest_7, ExampleTest) {
  uint8_t number = 0b011111111;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_8, ExampleTest) {
  uint8_t number = 0b011111100;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_9, ExampleTest) {
  uint8_t number = 0b000000000;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 1);
}

TEST(ParityTest_10, ExampleTest) {
  uint8_t number = 44;
  uint8_t result = check_parity(number);
  ASSERT_EQ(result, 0);
}

// aux carry tests
TEST(AuxCarryTest_1, ExampleTest) {
  uint8_t number1 = 0b00001111;
  uint8_t number2 = 0b00000001;
  uint8_t result = aux_carry_add(number1, number2);
  ASSERT_EQ(result, 1);
}

TEST(AuxCarryTest_2, ExampleTest) {
  uint8_t number1 = 0b00000111;
  uint8_t number2 = 0b00000001;
  uint8_t result = aux_carry_add(number1, number2);
  ASSERT_EQ(result, 0);
}

TEST(AuxCarryTest_3, ExampleTest) {
  uint8_t number1 = 0b00001101;
  uint8_t number2 = 0b00000011;
  uint8_t result = aux_carry_add(number1, number2);
  ASSERT_EQ(result, 1);
}

TEST(AuxCarryTest_4, ExampleTest) {
  uint8_t number1 = 0b00001000;
  uint8_t number2 = 0b00000111;
  uint8_t result = aux_carry_add(number1, number2);
  ASSERT_EQ(result, 0);
}


// zero tests
TEST(ZeroTest_1, ExampleTest) {
  uint8_t number = 0;
  uint8_t result = zero(number);
  ASSERT_EQ(result, 1);
}

TEST(ZeroTest_2, ExampleTest) {
  uint8_t number = 10;
  uint8_t result = zero(number);
  ASSERT_EQ(result, 0);
}

TEST(ZeroTest_3, ExampleTest) {
  uint8_t number = 1;
  uint8_t result = zero(number);
  ASSERT_EQ(result, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
