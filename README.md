# AoC in C

[Advent of Code](https://adventofcode.com) solutions written in C.

## 📥 Input Files

This project **does not include input files** from [Advent of Code](https://adventofcode.com), since they are unique for each user.

To run a puzzle solution, create the input file manually:

```bash
mkdir -p input
```

Then save your personal input as:

```text
input/YYYY-dayDD.txt
```

For example:

```text
input/2015-day01.txt
```

You can copy your puzzle input from the Advent of Code website after signing in.

## 🛠️ Build and Run

This project uses [`make`](https://www.gnu.org/software/make/) to build solutions.  
Make must be available on your system (e.g., included with MinGW-w64 on Windows or installed via a package manager on Linux/macOS).

To build and run a specific day's solution:

```bash
make run day=DD year=YYYY
```

**Example:**

```bash
make run day=01 year=2015
```

This compiles `src/2015/day01.c` and runs the resulting binary.

Your personal input should be placed at:

```text
input/2015-day01.txt
```

---

## ✅ Running Unit Tests

Each solution file includes unit tests based on example inputs from the Advent of Code problem description.  
To run these tests, invoke the compiled binary with the `test` argument:

```bash
./bin/dayDD test
```

**Example:**

```bash
./bin/day01 test
```

This will run the built-in test suite and report pass/fail results to the console.

---
