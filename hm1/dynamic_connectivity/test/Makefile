CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11 -g
CXXFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lgtest -lgtest_main -pthread

TARGET = dynamic_connectivity_tests

all: $(TARGET)

$(TARGET): dynamic_connectivity_tests.cpp ../src/dynamic_connectivity.c
	$(CXX) $(CXXFLAGS) dynamic_connectivity_tests.cpp ../src/dynamic_connectivity.c -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)