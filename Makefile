CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O2
SAN_FLAGS = -fsanitize=address,undefined -g

SRC = src/main.c src/cache.c
TARGET = build/cache_sim

.PHONY: all sanitize clean test

all: $(TARGET)

$(TARGET): $(SRC) src/cache.h
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

sanitize: $(SRC) src/cache.h
	@mkdir -p build
	$(CC) $(CFLAGS) $(SAN_FLAGS) $(SRC) -o $(TARGET)

test: sanitize
	./$(TARGET) -s 2 -E 1 -b 2 -p LRU -t traces/sample.trace

clean:
	rm -rf build
