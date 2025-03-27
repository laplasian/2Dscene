#include "factory.h"

#include <bemapiset.h>

#include "objects.h"
#include "scene.h"
#include "lib/slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Class * get_obj(const char * line) {
    int d1, d2, d3, d4;
    char name[10] = {};
    int num = sscanf(line, "%s %d %d %d %d", name, &d1, &d2, &d3, &d4);

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
    //print_message_at_scene("  ");
    print_message_at_scene(line);
    return NULL;
}

void * create_slist(FILE *file) {
    char line[max_line_size]={};
    fgets(line, max_line_size, file);

    void * slist = slist_create(sizeof(struct Class*));

    while (fgets(line, max_line_size, file)) {

        struct Class * parser_buff = get_obj(line);
        if (parser_buff == NULL) {
            continue;
        }

        struct Class ** obj = slist_prepend(slist); // Получаем указатель на новый элемент
        *obj = parser_buff;
    }
    return slist;
}

void delete_slist(void * slist) {
    size_t current = slist_first(slist);
    while (current != slist_stop(slist)) {
        void* obj = *(void **)slist_current(slist, current);
        delete(obj);
        current = slist_next(slist, current);
    }
    slist_destroy(slist, NULL);
}