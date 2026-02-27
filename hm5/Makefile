CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

TARGET = convex_hull
TEST_TARGET = test_convex_hull

all: $(TARGET) $(TEST_TARGET)

$(TARGET): convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) convex_hull.c -o $(TARGET) $(LDFLAGS)

$(TEST_TARGET): test_convex_hull.c convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -c convex_hull.c -o convex_hull.o
	$(CC) $(CFLAGS) -c test_convex_hull.c -o test_convex_hull.o
	$(CC) -DUNIT_TESTING convex_hull.o test_convex_hull.o -o $(TEST_TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run test