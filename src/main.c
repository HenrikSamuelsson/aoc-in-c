#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "2015/aoc_2015_day_01.h"
#include "2015/aoc_2015_day_02.h"
#include "input.h"

struct test_case
{
    const char *input;
    int expected;
};

/* -------------------- Day 1 tests -------------------- */

static bool run_day1_tests(void)
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

/* -------------------- Day 2 tests -------------------- */
/* AoC 2015 Day 2 examples:
   Part 1: "2x3x4" -> 58, "1x1x10" -> 43
   Part 2: "2x3x4" -> 34, "1x1x10" -> 14
*/
static bool run_day2_tests(void)
{
    const struct test_case part1_tests[] = {
        {"2x3x4\n", 58},
        {"1x1x10\n", 43},
    };

    for (size_t i = 0; i < sizeof(part1_tests) / sizeof(part1_tests[0]); ++i)
    {
        int result = solve_aoc_2015_day_02_part_1(part1_tests[i].input);
        if (result != part1_tests[i].expected)
        {
            printf("Day 2 Part 1 — Test %zu failed: \"%s\" -> expected %d, "
                   "got %d\n",
                   i + 1, part1_tests[i].input, part1_tests[i].expected,
                   result);
            return false;
        }
    }
    printf("Day 2 Part 1: all tests passed!\n");

    const struct test_case part2_tests[] = {
        {"2x3x4\n", 34},
        {"1x1x10\n", 14},
    };

    for (size_t i = 0; i < sizeof(part2_tests) / sizeof(part2_tests[0]); ++i)
    {
        int result = solve_aoc_2015_day_02_part_2(part2_tests[i].input);
        if (result != part2_tests[i].expected)
        {
            printf("Day 2 Part 2 — Test %zu failed: \"%s\" -> expected %d, "
                   "got %d\n",
                   i + 1, part2_tests[i].input, part2_tests[i].expected,
                   result);
            return false;
        }
    }
    printf("Day 2 Part 2: all tests passed!\n");
    return true;
}

static bool run_tests(void)
{
    bool ok1 = run_day1_tests();
    bool ok2 = run_day2_tests();
    return ok1 && ok2;
}

/* -------------------- Runners -------------------- */

static int run_day1(const char *path)
{
    char *buffer = read_input_alloc(path);
    if (!buffer)
    {
        perror(path);
        return 1;
    }

    int part_1_result = solve_aoc_2015_day_01_part_1(buffer);
    printf("AoC 2015, day 01, part 1: %d\n", part_1_result);

    int part2_result = solve_aoc_2015_day_01_part_2(buffer);
    printf("AoC 2015, day 01, part 2: %d\n", part2_result);

    free(buffer);
    return 0;
}

static int run_day2(const char *path)
{
    char *buffer = read_input_alloc(path);
    if (!buffer)
    {
        perror(path);
        return 1;
    }

    int part_1_result = solve_aoc_2015_day_02_part_1(buffer);
    printf("AoC 2015, day 02, part 1: %d\n", part_1_result);

    int part_2_result = solve_aoc_2015_day_02_part_2(buffer);
    printf("AoC 2015, day 02, part 2: %d\n", part_2_result);

    free(buffer);
    return 0;
}

/* -------------------- Main -------------------- */

static void print_usage(const char *prog)
{
    printf("Usage:\n");
    printf("  %s test\n", prog);
    printf("  %s 1 [path_day1]\n", prog);
    printf("  %s 2 [path_day2]\n", prog);
    printf("  %s [all] [path_day1] [path_day2]\n", prog);
    printf("\nDefaults:\n");
    printf("  path_day1 = data/aoc_2015_day_01_input.txt\n");
    printf("  path_day2 = data/aoc_2015_day_02_input.txt\n");
}

int main(int argc, char *argv[])
{
    const char *default_path1 = "data/aoc_2015_day_01_input.txt";
    const char *default_path2 = "data/aoc_2015_day_02_input.txt";

    if (argc > 1 && strcmp(argv[1], "help") == 0)
    {
        print_usage(argv[0]);
        return 0;
    }

    if (argc > 1 && strcmp(argv[1], "test") == 0)
    {
        return run_tests() ? 0 : 1;
    }

    /* Mode selection:
       - No args or "all": run both days (optionally with paths)
       - "1" [path] or "2" [path]: run that day only
    */
    const char *mode = (argc > 1) ? argv[1] : "all";

    if (strcmp(mode, "1") == 0)
    {
        const char *path1 = (argc > 2) ? argv[2] : default_path1;
        return run_day1(path1);
    }
    else if (strcmp(mode, "2") == 0)
    {
        const char *path2 = (argc > 2) ? argv[2] : default_path2;
        return run_day2(path2);
    }
    else
    {
        const char *path1 = (argc > 2) ? argv[2] : default_path1;
        const char *path2 = (argc > 3) ? argv[3] : default_path2;
        int rc1 = run_day1(path1);
        int rc2 = run_day2(path2);
        return (rc1 == 0 && rc2 == 0) ? 0 : 1;
    }
}
