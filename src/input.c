// input.c
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

char *read_input_alloc(const char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(fp);
        return NULL;
    }

    long filesize = ftell(fp);
    if (filesize < 0) {
        perror("ftell");
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    char *buffer = malloc(filesize + 1);
    if (!buffer) {
        perror("malloc");
        fclose(fp);
        return NULL;
    }

    size_t read = fread(buffer, 1, filesize, fp);
    if (ferror(fp)) {
        perror("fread");
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[read] = '\0';
    fclose(fp);
    return buffer;
}
