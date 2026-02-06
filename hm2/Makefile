CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = percolation_simulation

SRC = main.c \
      percolation/PercolationStats.c \
      percolation/percolation.c \
      dynamic_connectivity/dynamic_connectivity.c

INC = -Ipercolation -Idynamic_connectivity

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -lm -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
