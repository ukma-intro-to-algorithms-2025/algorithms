CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g

GTEST_LIBS = -lgtest -lgtest_main -pthread

TARGET = test_randomized_queue
OBJ = randomized_queue.o

.PHONY: all test valgrind clean

all: $(TARGET)

randomized_queue.o: randomized_queue.c randomized_queue.h
	$(CC) $(CFLAGS) -c randomized_queue.c -o randomized_queue.o

$(TARGET): test_randomized_queue.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) test_randomized_queue.cpp $(OBJ) $(GTEST_LIBS) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f *.o $(TARGET)
