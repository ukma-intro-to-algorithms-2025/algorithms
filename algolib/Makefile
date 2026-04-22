CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2 -lm
LIB = algolib.a

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)

DEMO_SRC = $(wildcard demo/*.c)
DEMO_BINS = $(DEMO_SRC:demo/%.c=demo/%_demo)

all: $(LIB) $(DEMO_BINS)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rcs $@ $^

demo/%_demo: demo/%.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

test: $(LIB)
	$(CC) $(CFLAGS) -o tests/test_all tests/test_all.c $(LIB)
	./tests/test_all

clean:
	rm -rf obj $(LIB) demo/*_demo tests/test_all

.PHONY: all test clean