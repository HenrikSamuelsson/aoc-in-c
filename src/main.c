#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "2015/aoc_2015_day_01.h"
#include "input.h"

struct test_case
{
    const char *input;
    int expected;
};

const struct test_case part_1_tests[] = {
    {"(())", 0}, {"()()", 0}, {"(((", 3},  {"(()(()(", 3},  {"))(((((", 3},
    {"())", -1}, {"))(", -1}, {")))", -3}, {")())())", -3},
};

bool run_tests(void)
{
    int num_tests = sizeof(part_1_tests) / sizeof(part_1_tests[0]);
    for (int i = 0; i < num_tests; ++i)
    {
        int result = solve_aoc_2015_day_01_part_1(part_1_tests[i].input);
        if (result != part_1_tests[i].expected)
        {
            printf("Test %d failed: input \"%s\" -> expected %d, got %d\n",
                   i + 1, part_1_tests[i].input, part_1_tests[i].expected,
                   result);
            return false;
        }
    }

    printf("All part 1 tests passed!\n");

    // Part 2 tests
    const struct test_case part2_tests[] = {
        {")", 1},
        {"()())", 5},
    };

    for (int i = 0; i < sizeof(part2_tests) / sizeof(part2_tests[0]); ++i)
    {
        int result = solve_aoc_2015_day_01_part_2(part2_tests[i].input);
        if (result != part2_tests[i].expected)
        {
            printf(
                "Part 2 Test %d failed: input \"%s\" -> expected %d, got %d\n",
                i + 1, part2_tests[i].input, part2_tests[i].expected, result);
            return false;
        }
    }

    printf("All part 2 tests passed!\n");
    return true;
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "test") == 0)
    {
        return run_tests() ? 0 : 1;
    }

    const char *path = (argc > 1) ? argv[1] : "data/2015-day01.txt";

    char *buffer = read_input_alloc(path);
    if (!buffer)
    {
        perror(path); // shows EXACT path it tried
        return 1;
    }

    int answer_p1 = solve_aoc_2015_day_01_part_1(buffer);
    printf("AoC 2015, day 01, part 1: %d\n", answer_p1);

    int answer_p2 = solve_aoc_2015_day_01_part_2(buffer);
    printf("AoC 2015, day 01, part 2: %d\n", answer_p2);

    free(buffer);
    return 0;
}
