#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAPE_SIZE 30000

void skip_whitespace(const char **src) {
    while (**src == ' ' || **src == '\t' || **src == '\n' || **src == '\r') {
        (*src)++;
    }
}

int match_word(const char *src, const char *word) {
    size_t len = strlen(word);
    return strncmp(src, word, len) == 0;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    if (argc < 2) {
        printf("Usage: %s <source.svo>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Cannot open source file");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *source = malloc(fsize + 1);
    fread(source, 1, fsize, f);
    source[fsize] = '\0';
    fclose(f);

    unsigned char tape[TAPE_SIZE] = {0};
    int ptr = 0;
    const char *src = source;

    while (*src) {
        skip_whitespace(&src);
        if (match_word(src, "сво")) {
            tape[ptr]++;
            src += strlen("сво");
        } else if (match_word(src, "гойда")) {
            tape[ptr]--;
            src += strlen("гойда");
        } else if (match_word(src, "zov")) {
            putchar(tape[ptr]);
            src += strlen("zov");
        } else if (*src == '>') {
            ptr++;
            if (ptr >= TAPE_SIZE) ptr = 0;
            src++;
        } else if (*src == '<') {
            ptr--;
            if (ptr < 0) ptr = TAPE_SIZE - 1;
            src++;
        } else if (*src == '\0') {
            break;
        } else {
            src++;
        }
    }

    free(source);
    return 0;
}
