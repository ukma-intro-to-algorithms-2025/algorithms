CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g

GTEST_LIBS = -lgtest -lgtest_main -pthread

TARGET = test_deque
OBJS = deque.o

.PHONY: all clean test valgrind

all: $(TARGET)

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c -o deque.o

$(TARGET): test_deque.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) test_deque.cpp $(OBJS) $(GTEST_LIBS) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f *.o $(TARGET)
