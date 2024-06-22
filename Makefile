CC = gcc

CFLAGS = -Wall -Wextra -pedantic -std=c17

TARGET = main

SRCS = art.c cpu.c

OBJS = ${SRCS:.c=.o}

INCDIR = .

${TARGET}: ${OBJS}
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
# The below should grab art.c, cpu.c etc with $< automatically subing in the first preqeu(%.c since
# only one each should be just the right file)
# $@ = %.o (where % is subbed in) so art.o etc 
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@ 

clean:
	rm -f ${OBJS} ${TARGET}

.PHONY: clean

