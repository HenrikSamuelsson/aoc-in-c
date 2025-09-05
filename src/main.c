#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===================== Declarations from other modules =====================
 */
/* Test runners (provided by each day module) */
extern bool run_day1_tests(void);
extern bool run_day2_tests(void);
extern bool run_day3_tests(void);

/* Solvers */
extern int solve_aoc_2015_day_01_part_1(const char *input);
extern int solve_aoc_2015_day_01_part_2(const char *input);
extern int solve_aoc_2015_day_02_part_1(const char *input);
extern int solve_aoc_2015_day_02_part_2(const char *input);
extern int solve_aoc_2015_day_03_part_1(const char *input);
extern int solve_aoc_2015_day_03_part_2(const char *input);

/* Input loader implemented in src/input.c */
extern char *read_input_alloc(const char *path);

/* ============================== Constants ==================================
 */

enum
{
    DECIMAL_BASE = 10
};

static const char *DEF_PATH_DAY1 = "data/aoc_2015_day_01_input.txt";
static const char *DEF_PATH_DAY2 = "data/aoc_2015_day_02_input.txt";
static const char *DEF_PATH_DAY3 = "data/aoc_2015_day_03_input.txt";

/* ============================== Utilities ==================================
 */

static void print_usage(const char *prog)
{
    printf("Usage:\n");
    printf("  %s test [day]\n", prog);
    printf("  %s <day> [path]\n", prog);
    printf("  %s all [path_day1] [path_day2] [path_day3]\n", prog);
    printf("\nRegistered days:\n");
    printf("  01  default: %s\n", DEF_PATH_DAY1);
    printf("  02  default: %s\n", DEF_PATH_DAY2);
    printf("  03  default: %s\n", DEF_PATH_DAY3);
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

/* Load file from explicit path if provided, otherwise from default.
 * Returns malloc'ed buffer or NULL on error. */
static char *load_input_or_default(const char *explicit_path,
                                   const char *default_path,
                                   const char **used_path_out)
{
    const char *path =
        explicit_path && explicit_path[0] ? explicit_path : default_path;
    if (used_path_out)
        *used_path_out = path;
    return read_input_alloc(path);
}

static int run_day_1(const char *maybe_path)
{
    const char *used = NULL;
    char *data = load_input_or_default(maybe_path, DEF_PATH_DAY1, &used);
    if (!data)
    {
        fprintf(stderr, "Failed to read input file for Day 1: %s\n",
                used ? used : "(null)");
        return 1;
    }
    int p1 = solve_aoc_2015_day_01_part_1(data);
    int p2 = solve_aoc_2015_day_01_part_2(data);
    printf("Day 1 (file: %s)\n", used);
    printf("  Part 1: %d\n", p1);
    printf("  Part 2: %d\n", p2);
    free(data);
    return 0;
}

static int run_day_2(const char *maybe_path)
{
    const char *used = NULL;
    char *data = load_input_or_default(maybe_path, DEF_PATH_DAY2, &used);
    if (!data)
    {
        fprintf(stderr, "Failed to read input file for Day 2: %s\n",
                used ? used : "(null)");
        return 1;
    }
    int p1 = solve_aoc_2015_day_02_part_1(data);
    int p2 = solve_aoc_2015_day_02_part_2(data);
    printf("Day 2 (file: %s)\n", used);
    printf("  Part 1: %d\n", p1);
    printf("  Part 2: %d\n", p2);
    free(data);
    return 0;
}

static int run_day_3(const char *maybe_path)
{
    const char *used = NULL;
    char *data = load_input_or_default(maybe_path, DEF_PATH_DAY3, &used);
    if (!data)
    {
        fprintf(stderr, "Failed to read input file for Day 3: %s\n",
                used ? used : "(null)");
        return 1;
    }
    int p1 = solve_aoc_2015_day_03_part_1(data);
    int p2 = solve_aoc_2015_day_03_part_2(data);
    printf("Day 3 (file: %s)\n", used);
    printf("  Part 1: %d\n", p1);
    printf("  Part 2: %d\n", p2);
    free(data);
    return 0;
}

static int run_all_days(const char *path1, const char *path2,
                        const char *path3)
{
    int rc = 0;
    rc |= run_day_1(path1);
    rc |= run_day_2(path2);
    rc |= run_day_3(path3);
    return rc;
}

/* ================================ Main =====================================
 */

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
            long d = strtol(argv[2], &end, DECIMAL_BASE);
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
        const char *path = (argc >= 3) ? argv[2] : NULL;
        return run_day_1(path);
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        const char *path = (argc >= 3) ? argv[2] : NULL;
        return run_day_2(path);
    }
    else if (strcmp(argv[1], "3") == 0)
    {
        const char *path = (argc >= 3) ? argv[2] : NULL;
        return run_day_3(path);
    }
    else if (strcmp(argv[1], "all") == 0)
    {
        const char *path1 = (argc >= 3) ? argv[2] : NULL;
        const char *path2 = (argc >= 4) ? argv[3] : NULL;
        const char *path3 = (argc >= 5) ? argv[4] : NULL;
        return run_all_days(path1, path2, path3);
    }

    fprintf(stderr, "Unknown command: %s\n", argv[1]);
    print_usage(argv[0]);
    return 1;
}
