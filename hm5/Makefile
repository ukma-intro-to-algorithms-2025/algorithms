CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

TARGET = convex_hull
TEST_TARGET = test_convex_hull

all: $(TARGET) $(TEST_TARGET)

# Основна програма (має main)
$(TARGET): convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) convex_hull.c -o $(TARGET) $(LDFLAGS)

# Тестова програма (тепер ми додаємо тестовий main окремо)
$(TEST_TARGET): test_convex_hull.c convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -c convex_hull.c -o convex_hull.o
	$(CC) $(CFLAGS) -c test_convex_hull.c -o test_convex_hull.o
	$(CC) -DUNIT_TESTING convex_hull.o test_convex_hull.o -o $(TEST_TARGET) $(LDFLAGS)

# Очищення
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

# Запуск основної програми
run: $(TARGET)
	./$(TARGET)

# Запуск тестів
test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run test