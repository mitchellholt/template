// file.c
//
// Mitchell Holt, Jan 2023

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "file.h"

#define INITIAL_BUFFER_SIZE 80

char *read_line(FILE *stream) {
    if (!stream) return NULL;
    int bufferSize = INITIAL_BUFFER_SIZE;
    char *buffer = malloc(sizeof(char) * INITIAL_BUFFER_SIZE);
    int numRead = 0;
    char c;

    while (true) {
        c = fgetc(stream);
        if (c == EOF && !numRead) {
            free(buffer);
            return NULL;
        }
        if (numRead == bufferSize) {
            bufferSize += INITIAL_BUFFER_SIZE;
            buffer = realloc(buffer, sizeof(char) * bufferSize);
        }
        if (c == '\n' || c == EOF) {
            buffer[numRead++] = '\0';
            return buffer;
        }
        buffer[numRead++] = c;
    }
}

// TODO
bool copy_file(char *existingPath, char *newName) {
    return false;
}
