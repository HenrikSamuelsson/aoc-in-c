cmake_minimum_required(VERSION 3.16)

project(aoc_in_c LANGUAGES C)

# Options
option(AOC_ENABLE_WARNINGS "Enable strict warnings" ON)
option(AOC_ENABLE_SANITIZERS "Enable Address/UB sanitizers (non-MSVC)" OFF)
option(AOC_BUILD_TESTING "Enable ctest target to run './aoc test'" ON)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Sources
set(AOC_SOURCES
    src/main.c
    src/input.c
    src/2015/aoc_2015_day_01.c
    src/2015/aoc_2015_day_02.c
)

add_executable(aoc ${AOC_SOURCES})
target_include_directories(aoc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/2015
)

# Warnings
if (AOC_ENABLE_WARNINGS)
    if (MSVC)
        target_compile_options(aoc PRIVATE /W4 /permissive-)
    else()
        target_compile_options(aoc PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wdouble-promotion -Wformat=2
            -Wno-unused-parameter
        )
    endif()
endif()

# Sanitizers
if (AOC_ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(aoc PRIVATE -fsanitize=address,undefined)
    target_link_options(aoc PRIVATE -fsanitize=address,undefined)
endif()

# On Windows, ensure console subsystem
if (WIN32)
    target_compile_definitions(aoc PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Testing: run built binary with 'test' subcommand
include(CTest)
if (AOC_BUILD_TESTING)
    add_test(NAME aoc_tests COMMAND aoc test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Install (optional)
install(TARGETS aoc RUNTIME DESTINATION bin)
