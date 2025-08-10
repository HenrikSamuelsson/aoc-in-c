CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I src -I include

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

SRC := $(SRC_DIR)/main.c \
       $(SRC_DIR)/2015/day01.c \
       $(SRC_DIR)/input.c

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET := $(BIN_DIR)/day01

.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@if not exist "$(OBJ_DIR)\2015" mkdir "$(OBJ_DIR)\2015"

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# ensure the object directory exists (Windows-safe)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
