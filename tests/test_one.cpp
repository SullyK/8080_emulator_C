#include <gtest/gtest.h>
#include <iostream>
#include "../src/art.h"
#include "../src/cpu.h"


TEST(OverflowTest, ExampleTest){
    uint8_t a = 23;
    uint8_t b = 33;
    uint8_t result = overflow_detected(a,b);

    ASSERT_EQ(result, 0);

}

TEST(testOne, ExampleTest){
    ASSERT_FALSE(1 == 2);
}

//TEST(testTwo, ExampleTest){
//    int result = add_numbers(1,2);
//ASSERT_TRUE(1 == result);
//}



int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
