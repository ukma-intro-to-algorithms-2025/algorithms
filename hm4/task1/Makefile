CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJ = insertion_sort.o selection_sort.o shell_sort.o test.o

all: test

test: $(OBJ)
	$(CC) $(CFLAGS) -o test $(OBJ)

insertion_sort.o: insertion_sort.c sort.h
	$(CC) $(CFLAGS) -c insertion_sort.c

selection_sort.o: selection_sort.c sort.h
	$(CC) $(CFLAGS) -c selection_sort.c

shell_sort.o: shell_sort.c sort.h
	$(CC) $(CFLAGS) -c shell_sort.c

test.o: test.c sort.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f *.o test