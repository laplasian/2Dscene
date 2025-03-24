#include "scene.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>

#include "factory.h"
#include "lib/console.h"
#include "new.h"
#include "lib/slist.h"

extern int field_width = 0;
extern int field_height = 0;

/* Output char using given color pair at given position. */
void scene_draw_point(Scene * scene, int x, int y, int color, int ch) {
    if (scene == NULL) {
        return;
    }
    if (scene->x1 < x < scene->x2 && scene->y1 < y < scene->y2) {
        con_gotoXY(x - scene->x1, y - scene->y1);
        con_setColor((short)color);
        con_outTxt("%c", ch);
    }
}

void init_colors() {
    con_initPair(COLOR_BORDER, CON_COLOR_BLACK, CON_COLOR_BLACK);
    con_initPair(COLOR_FIELD, CON_COLOR_GREEN, CON_COLOR_BLACK);
    con_initPair(COLOR_POINT, CON_COLOR_RED, CON_COLOR_BLACK);
}

void initial_draw(Scene * scene) {
    con_clearScr();
    con_gotoXY(TITLE_X, TITLE_Y);

    int i, j;
    for (i = 0; i < field_width; ++i) {
        for (j = 0; j < field_height; ++j) {
            int ch;
            int color;
            if (i == 0 || i == field_width-1 || j == 0 || j == field_height-1) {
                ch = CHAR_BORDER;
                color = COLOR_BORDER;
            } else {
                ch = CHAR_FIELD;
                color = COLOR_FIELD;
            }
            scene_draw_point(scene,i, j, color,ch);
        }
    }
}


Scene * create_scene(FILE *file) {
    char line[max_line_size]={};
    fgets(line, max_line_size, file);

    int scene_x1, scene_y1, scene_x2, scene_y2;
    if (sscanf(line, "%d %d %d %d", &scene_x1, &scene_y1, &scene_x2, &scene_y2) != 4) {
        printf("Error: expected 4 integers for scene dimensions\n");
        fclose(file);
        return NULL;
    }

    if (scene_x1 < 0 || scene_y1 < 0 || scene_x2 < 0 || scene_y2 < 0) {
        printf("Error: invalid scene dimensions\n");
        return NULL;
    }

    Scene * scene = malloc(sizeof(Scene));

    scene->x1 = min(scene_x1, scene_x2);
    scene->y1 = min(scene_y1, scene_y2);
    scene->x2 = max(scene_x1, scene_x2);
    scene->y2 = max(scene_y1, scene_y2);
    return scene;
}

void init_scene(Scene * scene) {
    int max_x = 0;
    int max_y = 0;

    con_init();
    con_hideCursor();
    init_colors();

    // calculate size of field
    con_getMaxXY(&max_x, &max_y);
    field_width = min(scene->x2-scene->x1, max_x);
    field_height = min(scene->y2-scene->y1, max_y);

    initial_draw(scene);
}

void draw_scene(Scene * scene, const void * slist) {
    size_t current = slist_first(slist);
    while (current != slist_stop(slist)) {
        void* obj = *(void **)slist_current(slist, current);
        draw(obj, scene);
        current = slist_next(slist, current);
    }
}

void destroy_scene(Scene * scene) {
    free(scene);
    con_clearScr();
    con_deinit();
}

void print_message_at_scene(const char * error) {
    static int count = 0;
    for (int i = 0; i < field_width; ++i) { // min(sizeof(error), field_width)
        char ch = error[i];
        if (error[i] == '\000') {
            break;
        }
        con_gotoXY(i, field_height + count + 3);
        con_setColor((short)3);
        con_outTxt("%c", error[i]);
    }
    count++;
}