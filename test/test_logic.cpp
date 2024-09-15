#include "../src/logic.h"
#include "../src/flags.h"
#include "../src/cpu.h"
#include <gtest/gtest.h>
#include <iostream>
 
TEST(and_register, NoChange){
    CPU cpu = {0};
    cpu.registers.A = 0xA;
    uint8_t fake_register = 0xA;
    and_register(&cpu, fake_register);
    ASSERT_EQ(cpu.registers.A, 0xA);
    
}

TEST(and_register, Basic1){
    CPU cpu = {0};
    cpu.registers.A = 50;
    uint8_t fake_register = 200;
    and_register(&cpu, fake_register);
    ASSERT_EQ(cpu.registers.A, 0x0);
}

