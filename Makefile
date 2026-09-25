CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

DEMO = memory_mapper_demo
TEST = test_memory_mapper

MAPPER_SOURCE = src/memory_mapper.c
MAIN_SOURCE = src/main.c
TEST_SOURCE = tests/test_memory_mapper.c

.PHONY: all demo test clean

all: $(DEMO) $(TEST)

$(DEMO): $(MAPPER_SOURCE) $(MAIN_SOURCE)
	$(CC) $(CFLAGS) $(MAPPER_SOURCE) $(MAIN_SOURCE) -o $(DEMO)

$(TEST): $(MAPPER_SOURCE) $(TEST_SOURCE)
	$(CC) $(CFLAGS) $(MAPPER_SOURCE) $(TEST_SOURCE) -o $(TEST)

demo: $(DEMO)
	./$(DEMO)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(DEMO) $(TEST)
