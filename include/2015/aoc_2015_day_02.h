#ifndef AOC_2015_DAY_02_H
#define AOC_2015_DAY_02_H

/* If included from C++, keep C linkage for the public API */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct Present {
    int length;
    int width;
    int height;
} Present;

int solve_aoc_2015_day_02_part_1(const char *instructions);
int solve_aoc_2015_day_02_part_2(const char *instructions);
bool run_day2_tests(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AOC_2015_DAY_02_H */
