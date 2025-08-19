#include "aoc_2015_day_02.h"
#include <stdlib.h>

static inline int min_int(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
static inline int max_int(int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }

// Parse a line of the form "LxWxH" (case-insensitive 'x').
// Advances *p past the end-of-line. Returns:
//   1 on success (and sets l, w, h),
//   0 when there's nothing more to parse (end of string),
//  -1 if the line is not a valid dimension (line is skipped).
static int parse_dims(const char **p, int *l, int *w, int *h)
{
    const char *s = *p;

    // Skip leading whitespace/newlines
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
    {
        s++;
    }
    if (*s == '\0')
    {
        *p = s;
        return 0;
    } // done

    char *e1, *e2, *e3;
    long L = strtol(s, &e1, 10);
    if (e1 == s || (*e1 != 'x' && *e1 != 'X'))
    {
        // Not a valid dimension line, skip to end-of-line
        while (*s && *s != '\n')
            s++;
        if (*s == '\n')
            s++;
        *p = s;
        return -1;
    }

    long W = strtol(e1 + 1, &e2, 10);
    if (e2 == (e1 + 1) || (*e2 != 'x' && *e2 != 'X'))
    {
        while (*s && *s != '\n')
            s++;
        if (*s == '\n')
            s++;
        *p = s;
        return -1;
    }

    long H = strtol(e2 + 1, &e3, 10);

    // Move to end-of-line (consume trailing spaces/CR, stop after '\n' if
    // present)
    while (*e3 && *e3 != '\n')
        e3++;
    if (*e3 == '\n')
        e3++;

    *p = e3;

    if (L <= 0 || W <= 0 || H <= 0)
        return -1;

    *l = (int)L;
    *w = (int)W;
    *h = (int)H;
    return 1;
}

int solve_aoc_2015_day_02_part_1(const char *instructions)
{
    if (!instructions)
        return 0;
    const char *p = instructions;
    long long total = 0;

    for (;;)
    {
        int l, w, h;
        int st = parse_dims(&p, &l, &w, &h);
        if (st == 0)
            break; // end
        if (st < 0)
            continue; // skip invalid/blank line

        int s1 = l * w;
        int s2 = w * h;
        int s3 = h * l;
        int surface = 2 * s1 + 2 * s2 + 2 * s3;
        int slack = min_int(s1, min_int(s2, s3));
        total += (long long)surface + (long long)slack;
    }

    return (int)total;
}

int solve_aoc_2015_day_02_part_2(const char *instructions)
{
    if (!instructions)
        return 0;
    const char *p = instructions;
    long long total = 0;

    for (;;)
    {
        int l, w, h;
        int st = parse_dims(&p, &l, &w, &h);
        if (st == 0)
            break; // end
        if (st < 0)
            continue; // skip invalid/blank line

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
