#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Class * get_objects(const char *filename) {
    FILE *file = fopen(filename, "r");

    struct Class * objects = malloc(max_obgect * sizeof(struct Class *));

    if (file == NULL) {
        return NULL;
    }

    char * line = malloc(max_line_size);
    if (line == NULL) {
        free(line);
        return NULL;
    }

    char* args[4];

    fgets(line, max_line_size, file);
    //sscanf(line, "%d %d %d %d", args[0], args[1], args[2], args[3]);

    while (fgets(line, max_line_size, file) != NULL) {
        printf("%s", line);
        //scanf(line, "%s, %d %d %d %d", line);
    }
    fclose(file);

    return NULL;
}
