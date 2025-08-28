<# 
cclean.ps1 — clean build wrapper for environments that have PowerShell.
Place this file in the repository root. No local shell aliases required.

Usage:
  ./cclean.ps1              # deletes the ./build directory safely

Notes:
- Assumes the build artifacts are always in ./build
- Uses Remove-Item with -Recurse and -Force, so be careful if you change the path
#>

$ErrorActionPreference = "Stop"

$buildDir = "build"

if (Test-Path $buildDir) {
  Write-Host "Removing build directory '$buildDir'..."
  Remove-Item -Recurse -Force $buildDir
  Write-Host "Clean complete."
} else {
  Write-Host "No build directory found, nothing to clean."
}
