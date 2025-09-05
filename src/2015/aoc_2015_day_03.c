#include "aoc_2015_day_03.h"
#include "test_case.h"
#include <stdio.h>
#include <stdlib.h>

int solve_aoc_2015_day_03_part_1(const char *input)
{
    // Stub.
    return -1;
}

int solve_aoc_2015_day_03_part_2(const char *input)
{
    // Stub.
    return -2;
}

/* -------------------- Day 3 tests -------------------- */
/* AoC 2015 Day 3 examples:
   Part 1: ">" -> 2, "^>v<" -> 4, "^v^v^v^v^v" -> 2
   Part 2: "^v" -> 3, "^>v<" -> 3, "^v^v^v^v^v" -> 11
*/
bool run_day3_tests(void)
{
    const struct test_case part1_tests[] = {
        {">\n", 2},
        {"^>v<\n", 4},
        {"^v^v^v^v^v", 2},
    };

    for (size_t i = 0; i < sizeof(part1_tests) / sizeof(part1_tests[0]); ++i)
    {
        int result = solve_aoc_2015_day_03_part_1(part1_tests[i].input);
        if (result != part1_tests[i].expected)
        {
            printf("Day 3 Part 1 - Test %zu failed: \"%s\" -> expected %d, "
                   "got %d\n",
                   i + 1, part1_tests[i].input, part1_tests[i].expected,
                   result);
            return false;
        }
    }
    printf("Day 3 Part 1: all tests passed!\n");

    const struct test_case part2_tests[] = {
        {"^v\n", 3},
        {"^>v<\n", 3},
        {"^v^v^v^v^v\n", 11},
    };

    for (size_t i = 0; i < sizeof(part2_tests) / sizeof(part2_tests[0]); ++i)
    {
        int result = solve_aoc_2015_day_03_part_2(part2_tests[i].input);
        if (result != part2_tests[i].expected)
        {
            printf("Day 3 Part 2 - Test %zu failed: \"%s\" -> expected %d, "
                   "got %d\n",
                   i + 1, part2_tests[i].input, part2_tests[i].expected,
                   result);
            return false;
        }
    }
    printf("Day 3 Part 2: all tests passed!\n");
    return true;
}
