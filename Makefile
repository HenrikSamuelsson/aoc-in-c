CC=gcc
CFLAGS=-Wall -Wextra -O2 -Isrc -Iinclude
BIN=bin

DAY   ?= $(day)
YEAR  ?= $(year)

all:
	@echo "Usage: make run day=DD year=YYYY"
	@echo "Example: make run day=01 year=2015"

run: $(TARGET)
	@if [ -z "$(YEAR)" ] || [ -z "$(DAY)" ]; then \
	  echo "Usage: make run year=2015 day=01"; exit 1; \
	fi
	@INPUT_FILE="$(CURDIR)/data/$(YEAR)-day$(DAY).txt"; \
	echo ">> $(TARGET) $$INPUT_FILE"; \
	$(TARGET) "$$INPUT_FILE"

.PHONY: all run
