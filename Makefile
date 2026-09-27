CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -pthread

SRC_DIR = src
TEST_DIR = tests

DEMO_SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/memory_mapper.c \
	$(SRC_DIR)/syscall_demo.c \
	$(SRC_DIR)/process_demo.c \
	$(SRC_DIR)/ipc_demo.c \
	$(SRC_DIR)/vm_demo.c \
	$(SRC_DIR)/file_demo.c \
	$(SRC_DIR)/thread_demo.c

DEMO_OBJECTS = $(DEMO_SOURCES:.c=.o)

TEST_SOURCES = \
	$(SRC_DIR)/memory_mapper.c \
	$(TEST_DIR)/test_memory_mapper.c

TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

TARGET = os_demo
TEST_TARGET = test_memory_mapper

.PHONY: all clean test demo

all: $(TARGET) $(TEST_TARGET)

demo: $(TARGET)
	./$(TARGET)

$(TARGET): $(DEMO_OBJECTS)
	$(CC) $(CFLAGS) $(DEMO_OBJECTS) -o $(TARGET) $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(TEST_TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(DEMO_OBJECTS) $(TEST_OBJECTS)
	rm -f $(TARGET) $(TEST_TARGET)
	rm -f data/syscall_test.txt
	rm -f data/file_demo.txt
