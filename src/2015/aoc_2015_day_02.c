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

    char *end_ptr = NULL;
    long L = strtol(chr, &end_ptr, DECIMAL_BASE);
    if (end_ptr == chr || (*end_ptr != 'x' && *end_ptr != 'X'))
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

    long W = strtol(end_ptr + 1, &end_ptr, 10);
    if (end_ptr == (end_ptr + 1) || (*end_ptr != 'x' && *end_ptr != 'X'))
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

    long H = strtol(end_ptr + 1, &end_ptr, 10);

    // Move to end-of-line (consume trailing spaces/CR, stop after '\n' if
    // present)
    while (*end_ptr && *end_ptr != '\n')
    {
        end_ptr++;
    }
    if (*end_ptr == '\n')
    {
        end_ptr++;
    }

    *cursor = end_ptr;

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
        int parse_status = parse_dims(&p, &l, &w, &h);
        if (parse_status == 0)
        {
            break; // end
        }
        if (parse_status < 0)
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
