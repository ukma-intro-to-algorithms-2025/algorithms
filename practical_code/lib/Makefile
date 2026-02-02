CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = statistical_measures

all: lib$(TARGET)_static.a lib$(TARGET)_dynamic.so

lib$(TARGET)_static.a: $(TARGET).o
	ar rcs $@ $<

lib$(TARGET)_dynamic.so: $(TARGET).o
	$(CC) -shared -o $@ $< -lm

$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f *.o *.a *.so

.PHONY: all clean