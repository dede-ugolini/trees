CC = g++
CFLAGS = -g -Wall -Wextra -fsanitize=address
SRC := $(shell find src -type f -name '*.cpp')
BIN := $(patsubst src/%.cpp, bin/%, $(SRC))

all: bin $(BIN)

clean:
	rm -rf bin

bin:
	mkdir -p bin

bin/%: src/%.cpp | bin
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all bin
