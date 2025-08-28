#include "aoc_2015_day_01.h"
#include "test_case.h"
#include <stdio.h>

int solve_aoc_2015_day_01_part_1(const char *instructions)
{
    int floor = 0;
    for (const char *instr = instructions; *instr != '\0'; ++instr)
    {
        if (*instr == '(')
        {
            floor++;
        }
        else if (*instr == ')')
        {
            floor--;
        }
    }
    return floor;
}

int solve_aoc_2015_day_01_part_2(const char *instructions)
{
    int floor = 0;
    int position = 0;
    for (const char *instr = instructions; *instr != '\0'; ++instr)
    {
        if (*instr == '(')
        {
            floor++;
        }
        else if (*instr == ')')
        {
            floor--;
        }
        position++;
        if (floor == -1)
        {
            break;
        }
    }
    return position;
}

/* -------------------- Day 1 tests -------------------- */

bool run_day1_tests(void)
{
    const struct test_case part1_tests[] = {
        {"(())", 0}, {"()()", 0}, {"(((", 3},  {"(()(()(", 3},  {"))(((((", 3},
        {"())", -1}, {"))(", -1}, {")))", -3}, {")())())", -3},
    };

    size_t num1 = sizeof(part1_tests) / sizeof(part1_tests[0]);
    for (size_t i = 0; i < num1; ++i)
    {
        int result = solve_aoc_2015_day_01_part_1(part1_tests[i].input);
        if (result != part1_tests[i].expected)
        {
            printf("Day 1 Part 1 — Test %zu failed: \"%s\" -> expected %d, "
                   "got %d\n",
                   i + 1, part1_tests[i].input, part1_tests[i].expected,
                   result);
            return false;
        }
    }
    printf("Day 1 Part 1: all tests passed!\n");

    const struct test_case part2_tests[] = {
        {")", 1},
        {"()())", 5},
    };

    size_t num2 = sizeof(part2_tests) / sizeof(part2_tests[0]);
    for (size_t i = 0; i < num2; ++i)
    {
        int result = solve_aoc_2015_day_01_part_2(part2_tests[i].input);
        if (result != part2_tests[i].expected)
        {
            printf("Day 1 Part 2 — Test %zu failed: \"%s\" -> expected %d, "
                   "got %d\n",
                   i + 1, part2_tests[i].input, part2_tests[i].expected,
                   result);
            return false;
        }
    }
    printf("Day 1 Part 2: all tests passed!\n");
    return true;
}
