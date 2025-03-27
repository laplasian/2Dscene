#include "factory.h"

#include <bemapiset.h>

#include "objects.h"
#include "scene.h"
#include "lib/slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Class * get_obj(const char * line, Scene * scene) {
    int d1, d2, d3, d4;
    char name[10] = {};
    int num = sscanf_s(line, "%s %d %d %d %d", name, 10, &d1, &d2, &d3, &d4);

    if (num == 3 && strcmp(name, "point") == 0) {
        return  new(Point, d1, d2);
    } else if (num == 5 && strcmp(name, "rect") == 0) {
        return  new(Rect, min(d1,d2), max(d1,d2), min(d3,d4), max(d3,d4));
    } else if (num == 4 && strcmp(name, "hline") == 0) {
        return  new(Hline, d1, min(d2, d3), max(d2, d3));
    } else if (num == 4 && strcmp(name, "vline") == 0) {
        return  new(Vline, min(d1, d2), max(d1, d2), d3);
    } else if (strcmp(line, "\n") == 0) {
        return NULL;
    }
    char message[max_line_size] = "bad line: ";
    scene_print_message(scene, strcat(message, line));
    return NULL;
}

void * create_slist(FILE *file, Scene * scene) {
    char line[max_line_size]={};
    fgets(line, max_line_size, file);

    void * slist = slist_create(sizeof(struct Class*));
    if (slist == NULL) {
        printf("slist_create error");
        return NULL;
    }

    while (fgets(line, max_line_size, file)) {

        struct Class * parser_buff = get_obj(line, scene);
        if (parser_buff == NULL) {
            continue;
        }

        struct Class ** obj = slist_prepend(slist);
        if (obj == NULL) {
            return NULL;
        }
        *obj = parser_buff;
    }
    return slist;
}

void delete_obj(void * data) {
    if (data != NULL) {
        return;
    }
    void* obj = *(void **)data;
    delete(obj);
}