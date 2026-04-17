CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -Iinclude

TARGET = lecture_12
TEST_TARGET = test_paths

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test

OBJS = digraph.o paths.o dfs.o bfs.o queue.o
MAIN_OBJS = $(TARGET).o $(OBJS)
TEST_OBJS = $(TEST_TARGET).o $(OBJS)

SRCS = $(SRC_DIR)/digraph.c $(SRC_DIR)/paths.c $(SRC_DIR)/dfs.c \
       $(SRC_DIR)/bfs.c $(SRC_DIR)/queue.c $(SRC_DIR)/lecture_12.c

TEST_SRCS = $(TEST_DIR)/test_paths.c

HEADERS = $(INCLUDE_DIR)/digraph.h $(INCLUDE_DIR)/paths.h $(INCLUDE_DIR)/paths_helper.h \
          $(INCLUDE_DIR)/dfs.h $(INCLUDE_DIR)/bfs.h $(INCLUDE_DIR)/queue.h

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJS)

$(TARGET).o: $(SRC_DIR)/lecture_12.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/lecture_12.c -o $(TARGET).o

digraph.o: $(SRC_DIR)/digraph.c $(INCLUDE_DIR)/digraph.h $(INCLUDE_DIR)/paths_helper.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/digraph.c -o digraph.o

dfs.o: $(SRC_DIR)/dfs.c $(INCLUDE_DIR)/dfs.h $(INCLUDE_DIR)/paths_helper.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/dfs.c -o dfs.o

bfs.o: $(SRC_DIR)/bfs.c $(INCLUDE_DIR)/bfs.h $(INCLUDE_DIR)/queue.h $(INCLUDE_DIR)/paths_helper.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/bfs.c -o bfs.o

queue.o: $(SRC_DIR)/queue.c $(INCLUDE_DIR)/queue.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/queue.c -o queue.o

paths.o: $(SRC_DIR)/paths.c $(INCLUDE_DIR)/paths.h $(INCLUDE_DIR)/paths_helper.h $(INCLUDE_DIR)/digraph.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/paths.c -o paths.o

$(TEST_TARGET).o: $(TEST_DIR)/test_paths.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_paths.c -o $(TEST_TARGET).o

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: all clean