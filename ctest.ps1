<# 
ctest.ps1 — portable test wrapper for environments that have PowerShell.
Place this file in the repository root. No local shell aliases required.

Usage:
  ./ctest.ps1              # run all tests discovered by CTest in ./build
  ./ctest.ps1 -V           # verbose (passes -V to ctest)

Notes:
- Assumes CMake/CTest are installed and available on PATH.
#>

param(
  [switch]$V
)

$ErrorActionPreference = "Stop"

$buildDir = "build"

if (-not (Test-Path $buildDir)) {
  Write-Error "Build directory '$buildDir' not found. Run ./cbuild.ps1 first."
  exit 1
}

$ctestArgs = @("--test-dir", $buildDir)
if ($V) { $ctestArgs += "-V" }

Write-Host "Running tests..."
& ctest @ctestArgs
