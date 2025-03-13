#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imports.h"
#include "scene.h"

void scene_add_obj(Scene* scene, struct Class* obj) {
    if (scene->size >= scene->capacity) {
        scene->capacity *= 2;
        scene->objects = realloc(scene->objects, scene->capacity * sizeof(struct Class*));
    }
    scene->objects[scene->size++] = obj;
}

Scene * make_scene(const char *filename) {
    FILE *file = fopen(filename, "r");

    Scene * scene = malloc(sizeof(Scene));

    scene->capacity = 4;
    scene->size = 0;
    scene->objects = malloc(scene->capacity * sizeof(struct Class*));

    if (file == NULL) {
        return NULL;
    }

    char * line = malloc(max_line_size);
    if (line == NULL) {
        free(line);
        return NULL;
    }

    fgets(line, max_line_size, file);
    int scene_x1, scene_y1, scene_x2, scene_y2;
    if (sscanf(line, "%d %d %d %d", &scene_x1, &scene_y1, &scene_x2, &scene_y2) != 4) {
        fprintf(stderr, "Error: expected 4 integers for scene dimensions\n");
        free(line);
        fclose(file);
        return NULL;
    }

    scene->height = scene_y2 - scene_y1;
    scene->width = scene_x2 - scene_x1;

    while (fgets(line, max_line_size, file) != NULL) {
        //printf("%s", line);
        char* token = strtok(line, " ");
        if (!token) {
            free(line);
            continue;
        }

        int x1, y1, x2, y2;

        if (strcmp(token, "point") == 0) {
            if (sscanf(line + strlen(token) + 1, "%d %d", &x1, &y1) == 2) {
                scene_add_obj(scene, new(Point, x1, y1));
            }
        }
        else if (strcmp(token, "rect") == 0) {
            if (sscanf(line + strlen(token) + 1, "%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
                scene_add_obj(scene, new(Rect, x1, y1, x2, y2));
            }
        }
        else if (strcmp(token, "hline") == 0) {
            if (sscanf(line + strlen(token) + 1, "%d %d %d", &x1, &x2, &y1) == 3) {
                scene_add_obj(scene, new(Hline, x1, x2, y1));
            }
        }
        else if (strcmp(token, "vline") == 0) {
            if (sscanf(line + strlen(token) + 1, "%d %d %d", &y1, &y2, &x1) == 3) {
                scene_add_obj(scene, new(Vline, y1, y2, x1));
            }
        }
    }

    free(line);
    fclose(file);
    return scene;
}
