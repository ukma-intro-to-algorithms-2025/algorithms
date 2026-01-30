CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -std=c++17 -g
CFLAGS = -Wall -Wextra -std=c11 -g
GTEST_LIBS = -lgtest -lgtest_main -pthread

TARGET = percolation_tests

all: $(TARGET)

percolation.o: ../src/percolation.c ../src/percolation.h
	$(CC) $(CFLAGS) -c ../src/percolation.c -o percolation.o

dynamic_connectivity.o: ../../dynamic_connectivity/src/dynamic_connectivity.c ../../dynamic_connectivity/src/dynamic_connectivity.h
	$(CC) $(CFLAGS) -c ../../dynamic_connectivity/src/dynamic_connectivity.c -o dynamic_connectivity.o

$(TARGET): percolation_test.cpp percolation.o dynamic_connectivity.o
	$(CXX) $(CXXFLAGS) percolation_test.cpp percolation.o dynamic_connectivity.o -o $@ $(GTEST_LIBS)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

clean:
	rm -f $(TARGET) *.o