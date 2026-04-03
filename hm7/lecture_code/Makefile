CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -Iinclude
TARGET = LLRB_tests

SRCS = src/BST.c src/LLRB.c src/LLRB_ops.c src/node.c
OBJS = BST.o LLRB.o LLRB_ops.o node.o LLRB_tests.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

BST.o: src/BST.c include/BST.h include/node.h
	$(CC) $(CFLAGS) -c src/BST.c

LLRB.o: src/LLRB.c include/LLRB.h include/LLRB_ops.h include/BST.h include/item.h
	$(CC) $(CFLAGS) -c src/LLRB.c

LLRB_ops.o: src/LLRB_ops.c include/LLRB_ops.h include/BST.h include/node.h
	$(CC) $(CFLAGS) -c src/LLRB_ops.c

node.o: src/node.c include/node.h include/item.h
	$(CC) $(CFLAGS) -c src/node.c

LLRB_tests.o: test/LLRB_tests.c include/LLRB.h include/BST.h
	$(CC) $(CFLAGS) -c test/LLRB_tests.c

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY: all clean run valgrind