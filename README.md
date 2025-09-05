# AoC in C

[Advent of Code](https://adventofcode.com) solutions written in C.

## 📥 Input Files

This project **does not include input files** from [Advent of Code](https://adventofcode.com), since they are unique for each user.

To run a puzzle solution, create a `data/` folder at the project root and place your inputs there using the naming convention:

```console
data/aoc_YYYY_day_DD_input.txt
```

For example:

```console
data/aoc_2015_day_01_input.txt
```

You can copy your puzzle input from the Advent of Code website after signing in.

---

## 🛠️ Build

This project uses [CMake](https://cmake.org/) + [Ninja](https://ninja-build.org/) for building.  
On Windows, use the provided PowerShell helper scripts:

```powershell
.\cclean.ps1   # remove the build/ directory
.\cbuild.ps1   # configure + build (default release build)
```

This generates `build/aoc.exe`.

---

## ▶️ Run Solutions

Use the unified CLI:

```powershell
.\build\aoc.exe <command> [args]
```

### Command Table

| Command               | Description                                       | Example                                    |
|-----------------------|---------------------------------------------------|--------------------------------------------|
| `test`                | Run all days' unit tests                          | `.\build\aoc.exe test`                     |
| `test <day>`          | Run unit tests for a specific day                 | `.\build\aoc.exe test 2`                   |
| `<day> [path]`        | Run solver for a specific day with optional input | `.\build\aoc.exe 1`                        |
|                       |                                                   | `.\build\aoc.exe 2 data/input.txt`         |
| `all [path1 path2 …]` | Run all days, optionally with per-day inputs      | `.\build\aoc.exe all`                      |

## ✅ Unit Tests

Each day has built-in tests based on the examples from the Advent of Code problem description.

Run them using the `test` subcommand:

```powershell
.\build\aoc.exe test        # run all days' tests
.\build\aoc.exe test 1      # run only Day 1 tests
.\build\aoc.exe test 2      # run only Day 2 tests
```

You can also run them via [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html):

```powershell
.\ctest.ps1          # run all registered tests
.\ctest.ps1 -Day 2   # run only Day 2
```

CTest integrates with CI systems and reports pass/fail status for each day.

---
