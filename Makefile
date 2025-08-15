# AoC in C - Windows-friendly Makefile (PowerShell/CMD)
SHELL := cmd
.SHELLFLAGS := /C

# ---- Toolchain ----
CC = gcc
CFLAGS = -std=c11 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS = -Iinclude -Iinclude/2015

# ---- Dirs ----
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# ---- Output ----
EXE = $(BINDIR)\aoc.exe

# ---- Sources ----
SRC_ROOT = $(SRCDIR)/main.c
SRC_SUB  = \
  $(SRCDIR)/input.c \
  $(SRCDIR)/2015/aoc_2015_day_01.c \
  $(SRCDIR)/2015/aoc_2015_day_02.c

# ---- Objects ----
OBJ_ROOT = $(BUILDDIR)/main.o
OBJ_SUB  = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC_SUB))
OBJ      = $(OBJ_ROOT) $(OBJ_SUB)

.PHONY: all run run1 run2 test clean dirs FORCE help

all: dirs $(EXE)

help:
	@echo make / make all  - build $(EXE)
	@echo make run         - run both days
	@echo make run1        - run day 1
	@echo make run2        - run day 2
	@echo make test        - run unit tests
	@echo make clean       - remove build outputs

dirs:
	@if not exist "$(BINDIR)"        mkdir "$(BINDIR)"
	@if not exist "$(BUILDDIR)"      mkdir "$(BUILDDIR)"
	@if not exist "$(BINDIR)\."      rem keep cmd happy
	@if not exist "$(BUILDDIR)\2015" mkdir "$(BUILDDIR)\2015"

# ---- Link ----
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

# ---- Compile rules ----
$(OBJ_ROOT): $(SRC_ROOT)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ---- Convenience ----
FORCE:

run: all FORCE
	@$(EXE)

run1: all FORCE
	@$(EXE) 1

run2: all FORCE
	@$(EXE) 2

test: all FORCE
	@$(EXE) test

clean:
	@if exist "$(BUILDDIR)" rmdir /S /Q "$(BUILDDIR)"
	@if exist "$(EXE)" del /Q "$(EXE)"
