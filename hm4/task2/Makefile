CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2 -I./include
CXXFLAGS = -Wall -Wextra -O2 -I./include -lgtest -lgtest_main -pthread
LDFLAGS = -lm

# Source files
POINT_SRC = src/point.c
BRUTE_SRC = apps/Brute.c
FAST_SRC = apps/Fast.c
TEST_SRC = tests/point_test.cpp

# Object files
POINT_OBJ = src/point.o
BRUTE_OBJ = apps/Brute.o
FAST_OBJ = apps/Fast.o

# Executables
BRUTE_EXEC = brute
FAST_EXEC = fast
TEST_EXEC = point_test

.PHONY: all clean test valgrind

all: $(BRUTE_EXEC) $(FAST_EXEC)

$(POINT_OBJ): $(POINT_SRC) include/point.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BRUTE_EXEC): $(BRUTE_SRC) $(POINT_OBJ)
	$(CC) $(CFLAGS) $(BRUTE_SRC) $(POINT_OBJ) $(LDFLAGS) -o $@

$(FAST_EXEC): $(FAST_SRC) $(POINT_OBJ)
	$(CC) $(CFLAGS) $(FAST_SRC) $(POINT_OBJ) $(LDFLAGS) -o $@

$(TEST_EXEC): $(TEST_SRC) $(POINT_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(POINT_OBJ) $(LDFLAGS) -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

valgrind: $(TEST_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_EXEC)

run-brute: $(BRUTE_EXEC)
	./$(BRUTE_EXEC) input.txt

run-fast: $(FAST_EXEC)
	./$(FAST_EXEC) input.txt

clean:
	rm -f src/*.o apps/*.o $(BRUTE_EXEC) $(FAST_EXEC) $(TEST_EXEC)

input.txt:
	echo "8\n0 0\n1 1\n2 2\n3 3\n0 1\n1 2\n2 3\n3 4" > input.txt