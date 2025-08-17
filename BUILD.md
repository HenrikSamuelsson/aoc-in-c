# Build with CMake

## Windows (WinLibs GCC)

You already have WinLibs GCC installed in `C:\tools\mingw64`.  
Run CMake with GCC explicitly set as the compiler:

```powershell
# Clean build folder (safe reset)
Remove-Item -Recurse -Force build -ErrorAction Ignore

# Configure with CMake + Ninja
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=C:/tools/mingw64/bin/gcc.exe

# Build (always use CMake, not make.exe)
cmake --build build --config Release
```

## Run tests

Equivalent to the old Makefile targets:

```powershell
# Internal test suite (same as `make test`)
ctest --test-dir build --output-on-failure

# Run convenience executables
cmake --build build --target run1
cmake --build build --target run2
```

## Common options

- `-D AOC_ENABLE_WARNINGS=ON` (default)  
- `-D AOC_ENABLE_SANITIZERS=ON` (non-MSVC)  
- `-D AOC_BUILD_TESTING=ON` (default; enables `ctest`)  
