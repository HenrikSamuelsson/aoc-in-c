#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declarations from your day modules */
extern bool run_day1_tests(void);
extern bool run_day2_tests(void);
extern bool run_day3_tests(void);

extern int solve_aoc_2015_day_01_part_1(const char *input);
extern int solve_aoc_2015_day_01_part_2(const char *input);
extern int solve_aoc_2015_day_02_part_1(const char *input);
extern int solve_aoc_2015_day_02_part_2(const char *input);
extern int solve_aoc_2015_day_03_part_1(const char *input);
extern int solve_aoc_2015_day_03_part_2(const char *input);

/* -------------------- Helpers -------------------- */

static void print_usage(const char *prog)
{
    printf("Usage:\n");
    printf("  %s test [day]\n", prog);
    printf("  %s <day> [path]\n", prog);
    printf("  %s all [path_day1] [path_day2] ...\n", prog);
    printf("\nRegistered days:\n");
    printf("  01  default: data/aoc_2015_day_01_input.txt\n");
    printf("  02  default: data/aoc_2015_day_02_input.txt\n");
    printf("  03  default: data/aoc_2015_day_03_input.txt\n");
}

static bool run_tests_for_day(int day)
{
    switch (day)
    {
    case 1:
        return run_day1_tests();
    case 2:
        return run_day2_tests();
    case 3:
        return run_day3_tests();
    default:
        return false;
    }
}

static bool run_all_tests(void)
{
    bool ok1 = run_day1_tests();
    bool ok2 = run_day2_tests();
    bool ok3 = run_day3_tests();
    return ok1 && ok2 && ok3;
}

/* -------------------- Main -------------------- */

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    /* ---- Test mode ---- */
    if (strcmp(argv[1], "test") == 0)
    {
        if (argc == 3)
        {
            char *end = NULL;
            long d = strtol(argv[2], &end, 10);
            if (*argv[2] != '\0' && end && *end == '\0')
            {
                bool ok = run_tests_for_day((int)d);
                if (!ok)
                {
                    fprintf(stderr, "Unknown day or tests failed: %ld\n", d);
                }
                return ok ? 0 : 1;
            }
            else
            {
                fprintf(stderr, "Invalid day: %s\n", argv[2]);
                print_usage(argv[0]);
                return 1;
            }
        }
        return run_all_tests() ? 0 : 1;
    }

    /* ---- Run a specific day ---- */
    if (strcmp(argv[1], "1") == 0)
    {
        /* TODO: load input from file if no argv[2] */
        fprintf(stderr, "Day 1 run not yet implemented in main.c\n");
        return 1;
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        fprintf(stderr, "Day 2 run not yet implemented in main.c\n");
        return 1;
    }
    else if (strcmp(argv[1], "3") == 0)
    {
        fprintf(stderr, "Day 3 run not yet implemented in main.c\n");
        return 1;
    }
    else if (strcmp(argv[1], "all") == 0)
    {
        fprintf(stderr, "Run-all not yet implemented in main.c\n");
        return 1;
    }

    fprintf(stderr, "Unknown command: %s\n", argv[1]);
    print_usage(argv[0]);
    return 1;
}
