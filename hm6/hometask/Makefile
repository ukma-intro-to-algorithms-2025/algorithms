# Простий Makefile для структури з папками

CC = gcc
CXX = g++
CFLAGS = -g -Wall -I./include
CXXFLAGS = -g -Wall -I./include

all: demo tests

demo: src/main.c src/BST.c src/node.c
	$(CC) $(CFLAGS) -o demo src/main.c src/BST.c src/node.c

tests: test/test.cpp src/BST.c src/node.c
	$(CXX) $(CXXFLAGS) -o tests test/test.cpp src/BST.c src/node.c

run: demo
	./demo

test: tests
	./tests

valgrind: tests
	valgrind --leak-check=full ./tests

clean:
	rm -f demo tests

.PHONY: all run test valgrind clean