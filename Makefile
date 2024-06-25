CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -pedantic -std=c17
CXXFLAGS = -std=c17 -Igoogletest/googletest/include
LDLIBS = -Lgoogletest/build/lib -lgtest -lgtest_main -pthread

MAIN_TARGET = main
TEST_TARGET = test_runner

MAIN_SRCS = src/art.c src/cpu.c
MAIN_OBJS = ${MAIN_SRCS:.c=.o}

TEST_SRCS = tests/test_one.cpp
TEST_OBJS = ${TEST_SRCS:.c=.o}

INCDIR = include



all: ${MAIN_TARGET} ${TEST_TARGET}

test: $(TEST_TARGET)
	./$(TEST_TARGET)
 
${MAIN_TARGET}: ${MAIN_OBJS}
	$(CC) $(CFLAGS) -o $@ $^

${TEST_TARGET}: ${TEST_OBJS} ${MAIN_OBJS}
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# The below should grab art.c, cpu.c etc with $< automatically subing in the first preqeu(%.c since
# only one each should be just the right file)
# $@ = %.o (where % is subbed in) so art.o etc 
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@ 

%.o: $.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f ${MAIN_OBJS} ${TEST_OBJS} ${MAIN_TARGET} ${TEST_TARGET}

.PHONY: all clean

