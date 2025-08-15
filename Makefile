# ---- MAKEFILE WITH DETAILED COMMENTS ----
# This is the original working Makefile with added explanations for learning.
# It builds and runs the AoC in C project on Windows using GNU Make + cmd.exe.
# -----------------------------------------------------------------------------
# AoC in C - Windows-friendly Makefile (PowerShell/CMD)
# Use Windows cmd.exe as the shell instead of default POSIX sh
SHELL := cmd
# Pass /C so cmd.exe runs the command string and then exits
.SHELLFLAGS := /C

# ---- Toolchain ----
# CC = name of the compiler to use
CC = gcc
# CFLAGS = compiler flags: standard, optimizations, and warnings
CFLAGS = -std=c11 -O2 -Wall -Wextra -Wpedantic
# CPPFLAGS = preprocessor flags: include paths for headers
CPPFLAGS = -Iinclude -Iinclude/2015

# ---- Dirs ----
# SRCDIR = path to the folder with source (.c) files
SRCDIR = src
# BUILDDIR = path to store compiled object (.o) files
BUILDDIR = build
# BINDIR = path to store the final executable
BINDIR = bin

# ---- Output ----
# EXE = name (and path) of the final program to build
EXE = $(BINDIR)\aoc.exe

# ---- Sources ----
# SRC_ROOT = main.c file (entry point)
SRC_ROOT = $(SRCDIR)/main.c
# SRC_SUB = all other .c files for helpers and AoC solutions
SRC_SUB  = \
  $(SRCDIR)/input.c \
  $(SRCDIR)/2015/aoc_2015_day_01.c \
  $(SRCDIR)/2015/aoc_2015_day_02.c

# ---- Objects ----
# OBJ_ROOT = compiled object for main.c
OBJ_ROOT = $(BUILDDIR)/main.o
# OBJ_SUB = compiled objects for each file in SRC_SUB
OBJ_SUB  = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC_SUB))
# OBJ = all object files needed to build the executable
OBJ      = $(OBJ_ROOT) $(OBJ_SUB)

# .PHONY declares targets that are not actual files, so make always runs them
.PHONY: all run run1 run2 test clean dirs FORCE help

# Default target: ensures output directories exist, then builds executable
all: dirs $(EXE)

# Help target: prints usage instructions
help:
	@echo make / make all  - build $(EXE)
	@echo make run         - run both days
	@echo make run1        - run day 1
	@echo make run2        - run day 2
	@echo make test        - run unit tests
	@echo make clean       - remove build outputs

# dirs target: create bin/ and build/ directories if they don't already exist
dirs:
	@if not exist "$(BINDIR)"        mkdir "$(BINDIR)"
	@if not exist "$(BUILDDIR)"      mkdir "$(BUILDDIR)"
	@if not exist "$(BINDIR)\."      rem keep cmd happy
	@if not exist "$(BUILDDIR)\2015" mkdir "$(BUILDDIR)\2015"

# ---- Link ----
# Link target: link all object files into the final executable
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

# ---- Compile rules ----
# Compile rule for main.c into build/main.o
$(OBJ_ROOT): $(SRC_ROOT)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Generic compile rule: compiles any src/%.c into build/%.o
# Uses subst to convert forward slashes to backslashes for mkdir on Windows
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ---- Convenience ----
# FORCE target: empty target used to force dependent targets to run
FORCE:

# run target: build everything, then run program for both days
run: all FORCE
	@$(EXE)

# run1 target: run program for only day 1
run1: all FORCE
	@$(EXE) 1

# run2 target: run program for only day 2
run2: all FORCE
	@$(EXE) 2

# test target: run program in test mode
test: all FORCE
	@$(EXE) test

# clean target: remove build directory and executable
clean:
	@if exist "$(BUILDDIR)" rmdir /S /Q "$(BUILDDIR)"
	@if exist "$(EXE)" del /Q "$(EXE)"
