CC=gcc
CFLAGS=-Wall -Wextra -O2
BIN=bin

all:
	@echo "Usage: make run day=DD year=YYYY"
	@echo "Example: make run day=01 year=2015"

run:
	$(CC) $(CFLAGS) -Isrc src/$(year)/day$(day).c src/input.c -o $(BIN)/day$(day)
	./$(BIN)/day$(day)

.PHONY: all run
