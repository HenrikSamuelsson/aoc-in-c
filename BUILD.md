# Build with CMake

## Windows (MinGW / WinLibs GCC)

You already have WinLibs GCC installed in `C:\tools\mingw64`.  
Run CMake with GCC explicitly set as the compiler:

```powershell
# Remove old build folder if switching compilers or after a failed configure
Remove-Item -Recurse -Force build -ErrorAction Ignore

# Configure and build
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=C:/tools/mingw64/bin/gcc.exe
cmake --build build --config Release

# Run tests (this executes `aoc test`)
ctest --test-dir build --output-on-failure
```

## Common options

- `-D AOC_ENABLE_WARNINGS=ON` (default)  
- `-D AOC_ENABLE_SANITIZERS=ON` (non-MSVC)  
- `-D AOC_BUILD_TESTING=ON` (default; enables `ctest` to run `aoc test`)  
