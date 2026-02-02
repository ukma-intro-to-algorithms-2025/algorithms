CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
LIB_DIR = ./lib
LIB_NAME = statistical_measures

all: main_static main_dynamic

main_static: main.o
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME)_static -lm

main_dynamic: main.o
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME)_dynamic -lm -Wl,-rpath=$(LIB_DIR)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main_static main_dynamic main.o

.PHONY: all clean