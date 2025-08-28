<#
cbuild.ps1 — portable build wrapper for environments that have PowerShell.
Configured to always use MinGW-w64 GCC for this AoC project.

Usage:
  ./cbuild.ps1              # configure (if needed) + build with default flags
  ./cbuild.ps1 -Reconfigure # force CMake reconfigure

Notes:
- Assumes MinGW-w64 GCC is installed at C:/tools/mingw64/bin/gcc.exe
- Generates compile_commands.json for tooling.
- Run ./cclean.ps1 if you want a completely fresh build directory.
#>

param(
  [switch]$Reconfigure
)

$ErrorActionPreference = "Stop"

$buildDir = "build"
$gccPath  = "C:/tools/mingw64/bin/gcc.exe"

if ($Reconfigure -or -not (Test-Path $buildDir)) {
  Write-Host "Configuring CMake with GCC at $gccPath ..."
  & cmake -S . -B $buildDir -G Ninja `
    -DCMAKE_C_COMPILER="$gccPath" `
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
}

Write-Host "Building..."
& cmake --build $buildDir
