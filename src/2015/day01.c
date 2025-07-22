#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 8192

int compute_final_floor(const char *instructions) {
    int floor = 0;
    for (const char *p = instructions; *p != '\0'; ++p) {
        if (*p == '(') {
            floor++;
        } else if (*p == ')') {
            floor--;
        }
    }
    return floor;
}

bool read_input(FILE *fp, char *buffer, size_t buffer_size) {
    size_t len = fread(buffer, 1, buffer_size - 1, fp);
    if (ferror(fp)) {
        return false;
    }
    buffer[len] = '\0';
    return true;
}

bool run_tests(void) {
    struct {
        const char *input;
        int expected;
    } tests[] = {
        {"(())", 0},
        {"()()", 0},
        {"(((", 3},
        {"(()(()(", 3},
        {"))(((((", 3},
        {"())", -1},
        {"))(", -1},
        {")))", -3},
        {")())())", -3},
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < num_tests; ++i) {
        int result = compute_final_floor(tests[i].input);
        if (result != tests[i].expected) {
            printf("Test %d failed: input \"%s\" → expected %d, got %d\n",
                   i + 1, tests[i].input, tests[i].expected, result);
            return false;
        }
    }

    printf("All tests passed!\n");
    return true;
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        return run_tests() ? 0 : 1;
    }

    FILE *fp = fopen("input/2015-day01.txt", "r");
    if (!fp) {
        perror("Failed to open input file");
        return 1;
    }

    char buffer[INPUT_BUFFER_SIZE];
    if (!read_input(fp, buffer, INPUT_BUFFER_SIZE)) {
        fprintf(stderr, "Failed to read input.\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    int floor = compute_final_floor(buffer);
    printf("Final floor: %d\n", floor);
    return 0;
}
