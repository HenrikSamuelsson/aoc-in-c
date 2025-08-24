#include "aoc_2015_day_02.h"
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
    const char *p = *cursor;

    if (!cursor || !out)
    {
        return -1; // defensive guard
    }

    // End-of-input?
    if (*p == '\0')
    {
        *cursor = p;
        return 0;
    }

    char *end_ptr = NULL;

    // L
    long L = strtol(p, &end_ptr, DECIMAL_BASE);
    if (end_ptr == p || (*end_ptr != 'x' && *end_ptr != 'X'))
    {
        while (*p && *p != '\n')
        {
            p++;
        }
        if (*p == '\n')
        {
            p++;
        }
        *cursor = p;
        return -1;
    }

    // W
    const char *w_start = end_ptr + 1;
    long W = strtol(w_start, &end_ptr, DECIMAL_BASE);
    if (end_ptr == w_start || (*end_ptr != 'x' && *end_ptr != 'X'))
    {
        while (*p && *p != '\n')
        {
            p++;
        }
        if (*p == '\n')
        {
            p++;
        }
        *cursor = p;
        return -1;
    }

    // H
    const char *h_start = end_ptr + 1;
    long H = strtol(h_start, &end_ptr, DECIMAL_BASE);

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
    if (L <= 0 || W <= 0 || H <= 0)
    {
        return -1;
    }

    out->length = (int)L;
    out->width = (int)W;
    out->height = (int)H;
    return 1;
}

int solve_aoc_2015_day_02_part_1(const char *instructions)
{
    if (!instructions)
    {
        return 0;
    }
    const char *p = instructions;
    long long total = 0;

    for (;;)
    {
        Present present;
        int parse_status = parse_dims(&p, &present);
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
    const char *p = instructions;
    long long total = 0;

    for (;;)
    {
        Present present;
        int parse_status = parse_dims(&p, &present);
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
