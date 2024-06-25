CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -pedantic -std=c17
CXXFLAGS = -std=c++17 
LDLIBS = -L/Users/sul/Documents/emulator/8080_emulator_C/googletest/build/lib -lgtest -lgtest_main -lgmock

MAIN_TARGET = main
TEST_TARGET = test_runner

MAIN_SRCS = src/art.c src/cpu.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

TEST_SRCS = tests/test_one.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o) $(MAIN_OBJS)

INCDIR = src/
GTEST_INCDIR = /Users/sul/Documents/emulator/8080_emulator_C/googletest/googletest/include
GMOCK_INCDIR = /Users/sul/Documents/emulator/8080_emulator_C/googletest/googlemock/include

all: $(MAIN_TARGET) $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCDIR) -I$(GMOCK_INCDIR) -c $< -o $@

clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all test clean

