#include <stdbool.h>

int solve_aoc_2015_day_01_part_1(const char *instructions)
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

int solve_aoc_2015_day_01_part_2(const char *instructions)
{
    int floor = 0;
    int position = 0;
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
        position++;
        if (floor == -1)
        {
            break;
        }
    }
    return position;
}
