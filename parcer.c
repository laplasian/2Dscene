#include "parcer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_object(char *str)
{
    if (strcmp(str, "") == 0)
        return screen;
    if (strcmp(str, "cyrcle") == 0)
        return cyrcle;
    if (strcmp(str, "rect") == 0)
        return rect;
    if (strcmp(str, "triangle") == 0)
        return triangle;
    if (strcmp(str, "point") == 0)
        return point;
    if (strcmp(str, "hline") == 0)
        return hline;
    if (strcmp(str, "vline") == 0)
        return vline;
    return screen;
}

char * read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length);
    if (buffer != NULL) {
        fread(buffer, 1, length, file);
    }
    fclose(file);
    return buffer;
}

int * get_args(char *str)
{
    int *args = malloc(4 * sizeof(int));
    char *token = strtok(str, " ");
    int i = 0;
    while (token != NULL) {
        args[i] = atoi(token);
        token = strtok(NULL, " ");
        i++;
    }
    return args;
}