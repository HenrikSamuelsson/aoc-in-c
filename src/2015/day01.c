#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

int compute_final_floor(const char *instructions)
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

struct test_case
{
    const char *input;
    int expected;
};

const struct test_case tests[] = {
    {"(())", 0}, {"()()", 0}, {"(((", 3},  {"(()(()(", 3},  {"))(((((", 3},
    {"())", -1}, {"))(", -1}, {")))", -3}, {")())())", -3},
};

bool run_tests(void)
{
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < num_tests; ++i)
    {
        int result = compute_final_floor(tests[i].input);
        if (result != tests[i].expected)
        {
            printf("Test %d failed: input \"%s\" → expected %d, got %d\n",
                   i + 1, tests[i].input, tests[i].expected, result);
            return false;
        }
    }

    printf("All tests passed!\n");
    return true;
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "test") == 0)
    {
        return run_tests() ? 0 : 1;
    }

    const char *path = "input/2015-day01.txt";
    char *buffer = read_input_alloc(path);
    if (!buffer)
    {
        return 1;
    }

    int floor = compute_final_floor(buffer);
    printf("Final floor: %d\n", floor);

    free(buffer);
    return 0;
}
