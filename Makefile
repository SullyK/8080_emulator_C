CC = gcc
CXX = g++ 
#TODO: make sure the -Werror are set as errors instead of warnings
#TODO: clear linker errors
CFLAGS = -Wall -Wextra -pedantic -std=c17 -Werror
CXXFLAGS = -std=c++17 -I./googletest/googletest/include -I./googletest/googletest -pthread
LDLIBS = -L./googletest/build/lib -lgtest -lgtest_main

MAIN_TARGET = main
TEST_TARGET = test_runner


MAIN_SRCS = src/art.c src/cpu.c src/main.c  src/add_funcs.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

HELPERS_MAIN_SRCS = src/art.c src/cpu.c src/add_funcs.c
HELPERS_OBJS = $(HELPERS_MAIN_SRCS:.c=.o) 
TEST_SRCS = test/test_flags.cpp test/test_interg_arth.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o) $(HELPERS_OBJS)


all: $(MAIN_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDLIBS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all test clean

