#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAPE_SIZE 30000
#define STACK_SIZE 1024

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

    const char *stack[STACK_SIZE];
    int stack_ptr = 0;

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
        } else if (match_word(src, "перемога")) {
            ptr++;
            if (ptr >= TAPE_SIZE) ptr = 0;
            src += strlen("перемога");
        } else if (match_word(src, "потужно")) {
            ptr--;
            if (ptr < 0) ptr = TAPE_SIZE - 1;
            src += strlen("потужно");
        } else if (match_word(src, "хрюко")) {
            if (tape[ptr] == 0) {
                int depth = 1;
                src += strlen("хрюко");
                while (*src && depth > 0) {
                    skip_whitespace(&src);
                    if (match_word(src, "хрюко")) {
                        depth++;
                        src += strlen("хрюко");
                    } else if (match_word(src, "стяг")) {
                        depth--;
                        src += strlen("стяг");
                    } else {
                        src++;
                    }
                }
            } else {
                stack[stack_ptr++] = src;
                src += strlen("хрюко");
            }
        } else if (match_word(src, "стяг")) {
            if (stack_ptr == 0) {
                fprintf(stderr, "Unmatched стяг\n");
                free(source);
                return 1;
            }
            if (tape[ptr] != 0) {
                src = stack[stack_ptr - 1] + strlen("хрюко");
            } else {
                stack_ptr--;
                src += strlen("стяг");
            }
        } else if (*src == '\0') {
            break;
        } else {
            src++;
        }
    }

    free(source);
    return 0;
}