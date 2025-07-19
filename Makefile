CC=gcc
CFLAGS=-Wall -Wextra -O2
BIN=bin

all:
	@echo "Usage: make day=DD year=YYYY"
	@echo "Example: make day=01 year=2015"

run:
	$(CC) $(CFLAGS) src/$(year)/day$(day).c -o $(BIN)/day$(day)
	./$(BIN)/day$(day)

.PHONY: all run
