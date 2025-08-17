#include <stdarg.h>
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

static const int DECIMAL_BASE = 10;

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

/* -------------------- Generic runner & registry -------------------- */

typedef int (*solve_fn)(const char *input);

typedef struct
{
    int year;
    int day; // 1..25
    const char *default_path;
    solve_fn part1;
    solve_fn part2;
} day_spec;

/* Registry: add new days here */
static const day_spec days[] = {
    {2015, 1, "data/aoc_2015_day_01_input.txt", solve_aoc_2015_day_01_part_1,
     solve_aoc_2015_day_01_part_2},
    {2015, 2, "data/aoc_2015_day_02_input.txt", solve_aoc_2015_day_02_part_1,
     solve_aoc_2015_day_02_part_2},
};
static const size_t days_count = sizeof(days) / sizeof(days[0]);

static inline const day_spec *find_day(int day_number)
{
    for (size_t i = 0; i < days_count; ++i)
    {
        if (days[i].day == day_number)
        {
            return &days[i];
        }
    }
    return NULL;
}

static int run_one_day(const day_spec *spec, const char *path_opt)
{
    const char *path = path_opt ? path_opt : spec->default_path;

    char *buffer = read_input_alloc(path);
    if (!buffer)
    {
        perror(path);
        return 1;
    }

    /* Zero-pad day to two digits for consistent output. */
    printf("AoC %d, day %02d, part 1: %d\n", spec->year, spec->day,
           spec->part1(buffer));
    printf("AoC %d, day %02d, part 2: %d\n", spec->year, spec->day,
           spec->part2(buffer));

    free(buffer);
    return 0;
}

static void print_usage(const char *prog)
{
    printf("Usage:\n");
    printf("  %s test\n", prog);
    printf("  %s <day> [path]\n", prog);
    printf("  %s all [path_day1] [path_day2] ...\n", prog);
    printf("\nRegistered days:\n");
    for (size_t i = 0; i < days_count; ++i)
    {
        printf("  %02d  default: %s\n", days[i].day, days[i].default_path);
    }
}

/* Prints an error message + usage, returns non-zero (failure). */
static int handle_invalid_usage(const char *prog, const char *fmt, ...)
{
    va_list var_args = {0};
    va_start(var_args, fmt);
    int written = vfprintf(stderr, fmt, var_args);
    va_end(var_args);

    if (written < 0)
    {
        perror("vfprintf failed");
        return 1;
    }

    (void)fputc('\n', stderr); /* newline after message */
    print_usage(prog);
    return 1;
}

/* -------------------- Main -------------------- */

int main(int argc, char *argv[])
{
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
       - No args or "all": run all registered days (optional per-day paths)
       - "<n>" [path]: run that day with optional input path
    */
    const char *mode = (argc > 1) ? argv[1] : "all";

    if (strcmp(mode, "all") == 0)
    {
        /* Optional custom paths for each day in registry order */
        int overall_result_code = 0;
        for (size_t i = 0; i < days_count; ++i)
        {
            const char *path_i = (2 + (int)i < argc) ? argv[2 + i] : NULL;
            int result_code = run_one_day(&days[i], path_i);
            if (result_code != 0)
            {
                overall_result_code = result_code;
            }
        }
        return overall_result_code;
    }

    /* If not "all", treat as specific day number */
    char *endptr = NULL;
    long day_num = strtol(mode, &endptr, DECIMAL_BASE);
    if (*mode != '\0' && *endptr == '\0')
    {
        const day_spec *spec = find_day((int)day_num);
        /* Unknown day */
        if (!spec)
        {
            return handle_invalid_usage(argv[0], "Unknown day: %ld", day_num);
        }
        const char *custom_path = (argc > 2) ? argv[2] : NULL;
        return run_one_day(spec, custom_path);
    }

    /* Fallback: unknown mode */
    return handle_invalid_usage(argv[0], "Unknown command: %s", mode);

    return 1;
}
