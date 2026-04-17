CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c99 -Iinclude $(shell pkg-config --cflags poppler-glib)
LIBS    = $(shell pkg-config --libs poppler-glib)
TARGET  = kmp_pdf

SRC_DIR = src
OBJ_DIR = .

OBJS    = kmp.o pdf_reader.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean