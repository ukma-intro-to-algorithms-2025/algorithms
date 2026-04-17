CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = maze_client
OBJS = maze_client.o maze.o solver.o queue.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c maze.h queue.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o