#include "aoc_2015_day_02.h"
#include "test_case.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief File-local constant used in parsing dimension strings.
 *
 * This is not part of the public API and are scoped to this translation unit
 * only.
 */
enum
{
    DECIMAL_BASE = 10 /**< Numerical base for strtol (decimal). */
};

static inline int min_int(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
static inline int max_int(int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }

// Parse a line "LxWxH" (case-insensitive 'x').
// Advances *cursor past the end-of-line.
// Returns: 1 on success; 0 at end-of-string; -1 if the line is invalid
// (skipped).
static int parse_dims(const char **cursor, Present *out)
{
    const char *input_char = *cursor;

    if (!cursor || !out)
    {
        return -1; // defensive guard
    }

    // End-of-input?
    if (*input_char == '\0')
    {
        *cursor = input_char;
        return 0;
    }

    char *end_ptr = NULL;

    // L
    long length = strtol(input_char, &end_ptr, DECIMAL_BASE);
    if (end_ptr == input_char || (*end_ptr != 'x' && *end_ptr != 'X'))
    {
        while (*input_char && *input_char != '\n')
        {
            input_char++;
        }
        if (*input_char == '\n')
        {
            input_char++;
        }
        *cursor = input_char;
        return -1;
    }

    // W
    const char *w_start = end_ptr + 1;
    long width = strtol(w_start, &end_ptr, DECIMAL_BASE);
    if (end_ptr == w_start || (*end_ptr != 'x' && *end_ptr != 'X'))
    {
        while (*input_char && *input_char != '\n')
        {
            input_char++;
        }
        if (*input_char == '\n')
        {
            input_char++;
        }
        *cursor = input_char;
        return -1;
    }

    // H
    const char *h_start = end_ptr + 1;
    long height = strtol(h_start, &end_ptr, DECIMAL_BASE);

    // Move to end-of-line (consume trailing chars until newline/EOS)
    while (*end_ptr && *end_ptr != '\n')
    {
        end_ptr++;
    }
    if (*end_ptr == '\n')
    {
        end_ptr++;
    }
    *cursor = end_ptr;

    // Validate and assign
    if (length <= 0 || width <= 0 || height <= 0)
    {
        return -1;
    }

    out->length = (int)length;
    out->width = (int)width;
    out->height = (int)height;
    return 1;
}

int solve_aoc_2015_day_02_part_1(const char *instructions)
{
    if (!instructions)
    {
        return 0;
    }
    const char *present_info = instructions;
    long long total = 0;

    for (;;)
    {
        Present present;
        int parse_status = parse_dims(&present_info, &present);
        if (parse_status == 0)
        {
            break; // end
        }
        if (parse_status < 0)
        {
            continue; // skip invalid/blank line
        }

        int surface_1 = present.length * present.width;
        int surface_2 = present.width * present.height;
        int surface_3 = present.height * present.length;
        int surface = (2 * surface_1) + (2 * surface_2) + (2 * surface_3);
        int slack = min_int(surface_1, min_int(surface_2, surface_3));
        total += (long long)surface + (long long)slack;
    }

    return (int)total;
}

int solve_aoc_2015_day_02_part_2(const char *instructions)
{
    if (!instructions)
    {
        return 0;
    }
    const char *present_info = instructions;
    long long total = 0;

    for (;;)
    {
        Present present;
        int parse_status = parse_dims(&present_info, &present);
        if (parse_status == 0)
        {
            break; // end
        }
        if (parse_status < 0)
        {
            continue; // skip invalid/blank line
        }

        // Bow is volume
        long long bow = (long long)present.length * (long long)present.width *
                        (long long)present.height;

        // Shortest perimeter = 2 * (sum of the two smallest edges)
        int sum = present.length + present.width + present.height;
        int longest =
            max_int(present.length, max_int(present.width, present.height));
        int wrap = 2 * (sum - longest);

        total += bow + wrap;
    }

    return (int)total;
}

/* -------------------- Day 2 tests -------------------- */
/* AoC 2015 Day 2 examples:
   Part 1: "2x3x4" -> 58, "1x1x10" -> 43
   Part 2: "2x3x4" -> 34, "1x1x10" -> 14
*/
bool run_day2_tests(void)
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
