#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_object_id(const char* token) {
    if (comp(token, "screen")) {
        return screen;
    }
    if (comp(token, "cyrcle")) {
        return cyrcle;
    }
    if (comp(token, "rect")) {
        return rect;
    }
    if (comp(token, "triangle")) {
        return triangle;
    }
    if (comp(token, "point")) {
        return point;
    }
    if (comp(token, "hline")) {
        return hline;
    }
    if (comp(token, "vline")) {
        return vline;
    }
    return 0;
}

int get_args_num(const char* token) {
    if (comp(token, "screen")) {
        return 4;
    }
    if (comp(token, "cyrcle")) {
        return 3;
    }
    if (comp(token, "rect")) {
        return 4;
    }
    if (comp(token, "triangle")) {
        return 6;
    }
    if (comp(token, "point")) {
        return 2;
    }
    if (comp(token, "hline")) {
        return 3;
    }
    if (comp(token, "vline")) {
        return 3;
    }
    return 0;
}

Object ** get_objects(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    char * line = malloc(max_line_size);
    Object ** objects = malloc(max_line_size * sizeof(NULL));
    if (objects == NULL || line == NULL) {
        free(line);
        free(objects);
        return NULL;
    }

    while (fgets(line, max_line_size, file) != NULL) {
        (*objects) = malloc(sizeof(Object));
        char *token = strtok(line, " ");
        if (token == NULL) {
            continue;
        }

        (*objects)->type = get_object_id(token);
        (*objects)->num_args = get_args_num(token);
        (*objects)->args = malloc(4 * sizeof(int));
        if ((*objects)->args == NULL) {
            free(line);
            free(objects);
            return NULL;
        }
        for (size_t i = 0; i < (*objects)->num_args; ++i) {
            token = strtok(NULL, " ");
            printf("%s ", token);
            if (token == NULL) {
                free(line);
                free(objects);
                return NULL;
            }
            (*objects)->args[i] = atoi(token);
        }
        ++ objects;
    }
    fclose(file);
    return objects;
}
