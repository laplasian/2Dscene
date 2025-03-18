//
// Created by user on 18.03.2025.
//

#include "factory.h"
#include "objects.h"
#include "scene.h"
#include "lib/slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Class * get_obj(const char * line) {
    int d1, d2, d3, d4;
    char name[max_line_size] = {};
    int num = sscanf(line, "%s %d %d %d %d", name, &d1, &d2, &d3, &d4);

    if (num == 3 && strcmp(name, "point") == 0) {
        return  new(Point, d1, d2);
    } else if (num == 5 && strcmp(name, "rect") == 0) {
        return  new(Rect, d1, d2, d3, d4);
    } else if (num == 4 && strcmp(name, "hline") == 0) {
        return  new(Hline, d1, d2, d3);
    } else if (num == 4 && strcmp(name, "vline") == 0) {
        return  new(Vline, d1, d2, d3);
    }
    printf("lol");
    return NULL;
}

Scene * create_scene(const char * file_name) {
    FILE *file = fopen(file_name, "r");

    char line[max_line_size]={};
    fgets(line, max_line_size, file);

    int scene_x1, scene_y1, scene_x2, scene_y2;
    if (sscanf(line, "%d %d %d %d", &scene_x1, &scene_y1, &scene_x2, &scene_y2) != 4) {
        printf("Error: expected 4 integers for scene dimensions\n");
        fclose(file);
        return NULL;
    }
    Scene * scene = malloc(sizeof(Scene));

    scene->x1 = scene_x1;
    scene->y1 = scene_y1;
    scene->x2 = scene_x2;
    scene->y2 = scene_y2;

    scene->slist = slist_create(sizeof(struct Class*));

    while (fgets(line, max_line_size, file)) {
        struct Class * obj = slist_prepend(scene->slist); // Получаем указатель на новый элемент
        *obj = *get_obj(line);
    }

    return scene;
}

