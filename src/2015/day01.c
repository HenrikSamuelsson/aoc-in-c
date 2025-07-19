#include <stdio.h>

int main(void) {
    FILE *fp = fopen("input/2015-day01.txt", "r");
    if (!fp) {
        perror("Failed to open input file");
        return 1;
    }

    int floor = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '(') {
            floor++;
        } else if (ch == ')') {
            floor--;
        }
    }

    fclose(fp);
    printf("Final floor: %d\n", floor);
    return 0;
}
