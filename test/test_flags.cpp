#include <gtest/gtest.h>
#include <iostream>
#include "../src/art.h"

//overflow tests

TEST(OverflowTest_1, ExampleTest){
    uint8_t a = 23;
    uint8_t b = 33;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

TEST(OverflowTest_2, ExampleTest){
    uint8_t a = 255;
    uint8_t b = 1;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 1);
}

TEST(OverflowTest_3, ExampleTest){
    uint8_t a = 255;
    uint8_t b = 0;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

TEST(OverflowTest_4, ExampleTest){
    uint8_t a = 127;
    uint8_t b = 128;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

TEST(OverflowTest_5, ExampleTest){
    uint8_t a = 128;
    uint8_t b = 127;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

TEST(OverflowTest_6, ExampleTest){
    uint8_t a = 128;
    uint8_t b = 128;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 1);
}
 
TEST(OverflowTest_7, ExampleTest){
uint8_t a = 2;
uint8_t b = 254;
uint8_t result = unsigned_addition_carry_check(a,b);
ASSERT_EQ(result, 1);
}

TEST(OverflowTest_8, ExampleTest){
    uint8_t a = 0;
    uint8_t b = 0;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

TEST(OverflowTest_9, ExampleTest){
    uint8_t a = 255;
    uint8_t b = 0;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

TEST(OverflowTest_10, ExampleTest){
    uint8_t a = 250;
    uint8_t b = 5;
    uint8_t result = unsigned_addition_carry_check(a,b);
    ASSERT_EQ(result, 0);
}

//underflow test
TEST(UnderflowTest_1, ExampleTest){
    uint8_t a = 1;
    uint8_t b = 2;
    uint8_t result = unsigned_subtract_carry_check(a,b);
    ASSERT_EQ(result, 1);
}

 TEST(UnderflowTest_2, ExampleTest){
    uint8_t a = 2;
    uint8_t b = 1;
    uint8_t result = unsigned_subtract_carry_check(a,b);
    ASSERT_EQ(result, 0);
}
 
 TEST(UnderflowTest_3, ExampleTest){
    uint8_t a = 255;
    uint8_t b = 1;
    uint8_t result = unsigned_subtract_carry_check(a,b);
    ASSERT_EQ(result, 0);
}
 
 
 TEST(UnderflowTest_4, ExampleTest){
    uint8_t a = 1;
    uint8_t b = 255;
    uint8_t result = unsigned_subtract_carry_check(a,b);
    ASSERT_EQ(result, 1);
}
                   

 
 
//signed tests
TEST(CheckSignedTest_1, ExampleTest){
    uint8_t number = 0b10000000;
    uint8_t result =  check_signed_bit(number);
    ASSERT_EQ(result, 1);
}

TEST(CheckSignedTest_2, ExampleTest){
    uint8_t number = 0b00000000;
    uint8_t result =  check_signed_bit(number);
    ASSERT_EQ(result, 0);
}

TEST(CheckSignedTest_3, ExampleTest){
    uint8_t number = 0b00000001;
    uint8_t result =  check_signed_bit(number);
    ASSERT_EQ(result, 0);
}

TEST(CheckSignedTest_4, ExampleTest){
    uint8_t number = 0b11111110;
    uint8_t result =  check_signed_bit(number);
    ASSERT_EQ(result, 1);
}

//parity tests 
TEST(ParityTest_1, ExampleTest){
    uint8_t number = 0b10101010;
    uint8_t result = check_parity(number);
    ASSERT_EQ(result, 1);
}

TEST(ParityTest_2, ExampleTest){
    uint8_t number = 0b00001111;
    uint8_t result = check_parity(number);
    ASSERT_EQ(result, 1);
}
 
TEST(ParityTest_3, ExampleTest){
uint8_t number = 0b11110000;
uint8_t result = check_parity(number);
ASSERT_EQ(result, 1);
}

TEST(ParityTest_4, ExampleTest){
uint8_t number = 0b01010101;
uint8_t result = check_parity(number);
ASSERT_EQ(result, 1);
}
 
TEST(ParityTest_5, ExampleTest){
uint8_t number = 0b011110001;
uint8_t result = check_parity(number);
ASSERT_EQ(result, 0);
}
 
TEST(ParityTest_6, ExampleTest){
uint8_t number = 0b011110111;
uint8_t result = check_parity(number);
ASSERT_EQ(result, 0);
}
 
TEST(ParityTest_7, ExampleTest){
uint8_t number = 0b011111111;
uint8_t result = check_parity(number);
ASSERT_EQ(result, 1);
}
 
TEST(ParityTest_8, ExampleTest){
uint8_t number = 0b011111100;
uint8_t result = check_parity(number);
ASSERT_EQ(result, 1);
}

TEST(ParityTest_9, ExampleTest){
uint8_t number = 0b000000000;
uint8_t result = check_parity(number);
ASSERT_EQ(result,1);
}
 
 
// aux carry tests
TEST(AuxCarryTest_1, ExampleTest){
uint8_t number = 0b00001111;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 1);
}

TEST(AuxCarryTest_2, ExampleTest){
uint8_t number = 0b00000111;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 0);
}
    
TEST(AuxCarryTest_3, ExampleTest){
uint8_t number = 0b1110111;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 0);
}   
     
TEST(AuxCarryTest_4, ExampleTest){
uint8_t number = 0b11110000;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 0);
}   

TEST(AuxCarryTest_5, ExampleTest){
uint8_t number = 0b11110000;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 0);
}                          

TEST(AuxCarryTest_6, ExampleTest){
uint8_t number = 0b11001011;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 1);
}

 
TEST(AuxCarryTest_7, ExampleTest){
uint8_t number = 0b11001011;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 1);
}                    

 
TEST(AuxCarryTest_8, ExampleTest){
uint8_t number = 0b11001100;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 1);
}                    

TEST(AuxCarryTest_9, ExampleTest){
uint8_t number = 0b11001001;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 0);
}

 
TEST(AuxCarryTest_10, ExampleTest){
uint8_t number = 0b11001011;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 1);
}                          
 
TEST(AuxCarryTest_11, ExampleTest){
uint8_t number = 0b11011011;
uint8_t result = set_aux_carry(number);
ASSERT_EQ(result, 1);
}                          

//zero tests
TEST(ZeroTest_1, ExampleTest){
    uint8_t number = 0;
    uint8_t result = zero(number);
    ASSERT_EQ(result,1);
}

TEST(ZeroTest_2, ExampleTest){
    uint8_t number = 10;
    uint8_t result = zero(number);
    ASSERT_EQ(result,0);
}
                     
TEST(ZeroTest_3, ExampleTest){
    uint8_t number = 1;
    uint8_t result = zero(number);
    ASSERT_EQ(result,0);
}                     

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
