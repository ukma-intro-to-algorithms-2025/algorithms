CC = gcc
CFLAGS = -Wall -Wextra -O2 -g

all: two_stacks

two_stacks: two_stacks.o stack.o
	$(CC) $(CFLAGS) -o two_stacks two_stacks.o stack.o

two_stacks.o: two_stacks.c stack.h
	$(CC) $(CFLAGS) -c two_stacks.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f two_stacks *.o