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

// Parse a line of the form "LxWxH" (case-insensitive 'x').
// Advances *p past the end-of-line. Returns:
//   1 on success (and sets l, w, h),
//   0 when there's nothing more to parse (end of string),
//  -1 if the line is not a valid dimension (line is skipped).
static int parse_dims(const char **cursor, int *length, int *width,
                      int *height)
{
    const char *chr = *cursor;

    // Skip leading whitespace/newlines
    while (*chr == ' ' || *chr == '\t' || *chr == '\r' || *chr == '\n')
    {
        chr++;
    }
    if (*chr == '\0')
    {
        *cursor = chr;
        return 0;
    } // done

    char *e1;
    long L = strtol(chr, &e1, DECIMAL_BASE);
    if (e1 == chr || (*e1 != 'x' && *e1 != 'X'))
    {
        // Not a valid dimension line, skip to end-of-line
        while (*chr && *chr != '\n')
        {
            chr++;
        }
        if (*chr == '\n')
        {
            chr++;
        }
        *cursor = chr;
        return -1;
    }

    char *e2;
    long W = strtol(e1 + 1, &e2, 10);
    if (e2 == (e1 + 1) || (*e2 != 'x' && *e2 != 'X'))
    {
        while (*chr && *chr != '\n')
        {
            chr++;
        }
        if (*chr == '\n')
        {
            chr++;
        }
        *cursor = chr;
        return -1;
    }

    char *e3;
    long H = strtol(e2 + 1, &e3, 10);

    // Move to end-of-line (consume trailing spaces/CR, stop after '\n' if
    // present)
    while (*e3 && *e3 != '\n')
        e3++;
    if (*e3 == '\n')
        e3++;

    *cursor = e3;

    if (L <= 0 || W <= 0 || H <= 0)
    {
        return -1;
    }

    *length = (int)L;
    *width = (int)W;
    *height = (int)H;
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
        int l, w, h;
        int st = parse_dims(&p, &l, &w, &h);
        if (st == 0)
        {
            break; // end
        }
        if (st < 0)
        {
            continue; // skip invalid/blank line
        }

        int surface_1 = l * w;
        int surface_2 = w * h;
        int surface_3 = h * l;
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
        int l, w, h;
        int parse_status = parse_dims(&p, &l, &w, &h);
        if (parse_status == 0)
        {
            break; // end
        }
        if (parse_status < 0)
        {
            continue; // skip invalid/blank line
        }

        // Bow is volume
        long long bow = (long long)l * (long long)w * (long long)h;

        // Shortest perimeter = 2 * (sum of the two smallest edges)
        int sum = l + w + h;
        int longest = max_int(l, max_int(w, h));
        int wrap = 2 * (sum - longest);

        total += bow + wrap;
    }

    return (int)total;
}
