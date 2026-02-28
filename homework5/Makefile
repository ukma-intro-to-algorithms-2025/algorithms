CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests

SOURCES = $(SRC_DIR)/geometry.c $(SRC_DIR)/quicksort.c $(SRC_DIR)/mergesort.c $(SRC_DIR)/hull.c $(SRC_DIR)/main.c
TEST_SOURCES = $(TEST_DIR)/test_convex.c

OBJECTS = $(SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

TARGET = convex_hull
TEST_TARGET = test_convex_hull

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(SRC_DIR)/main.o, $(OBJECTS))
	$(CC) $(TEST_OBJECTS) $(filter-out $(SRC_DIR)/main.o, $(OBJECTS)) -o $(TEST_TARGET) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean run test