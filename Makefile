CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = test_memory_mapper

SOURCES = src/memory_mapper.c tests/test_memory_mapper.c

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
