#include "scene.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>

#include "factory.h"
#include "lib/console.h"
#include "new.h"
#include "lib/slist.h"

/* Output char using given color pair at given position. */
void scene_draw_point(Scene * scene, int x, int y, int color, int ch) {
    if (scene == NULL) {
        return;
    }
    if (scene->x1 <= x && x <= scene->x2 && scene->y1 <= y && y <= scene->y2) {
        con_gotoXY(x - scene->x1, y - scene->y1);
        con_setColor((short)color);
        con_outTxt("%c", ch);
    }
}

void scene_print_message(Scene * scene, const char * error) {
    for (int i = 0; i < scene->max_width; ++i) {
        if (error[i] == '\000') {
            break;
        }
        con_gotoXY(i, scene->y2 + scene->message_count);
        con_setColor((short)2);
        con_outTxt("%c", error[i]);
    }
    scene->message_count++;
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
    for (i = scene->x1; i < scene->x2; ++i) {
        for (j = scene->y1; j < scene->y2; ++j) {
            int ch;
            int color;
            if (i == scene->x1 || i == scene->x2 - 1 || j == scene->y1 || j == scene->y2 - 1) {
                ch = CHAR_BORDER;
                color = COLOR_BORDER;
                scene_draw_point(scene,i, j, color,ch);
            }
        }
    }
    scene_print_message(scene, "press escape to exit   ");
}


Scene * create_scene(FILE *file) {
    char line[max_line_size]={};
    fgets(line, max_line_size, file);

    int scene_x1, scene_y1, scene_x2, scene_y2;
    if (sscanf_s(line, "%d %d %d %d", &scene_x1, &scene_y1, &scene_x2, &scene_y2) != 4) {
        printf("Error: expected 4 integers for scene dimensions\n");
        return NULL;
    }

    if (scene_x1 < 0 || scene_y1 < 0 || scene_x2 < 0 || scene_y2 < 0) {
        printf("Error: invalid scene dimensions\n");
        return NULL;
    }

    Scene * scene = malloc(sizeof(Scene));
    if (scene == NULL) {
        printf("scene malloc error");
        return NULL;
    }

    scene->x1 = min(scene_x1, scene_x2);
    scene->y1 = min(scene_y1, scene_y2);
    scene->x2 = max(scene_x1, scene_x2);
    scene->y2 = max(scene_y1, scene_y2);

    scene->message_count = 1;

    return scene;
}

void init_scene(Scene * scene) {
    con_init();
    con_hideCursor();
    init_colors();

    // calculate size of field
    con_getMaxXY(&scene->max_width, &scene->max_height);

    if (scene->max_width < scene->x2-scene->x1 || scene->max_height < scene->y2-scene->y1) {
        scene->x2 = scene->x1 + scene->max_width;
        scene->y2 = scene->y1 + scene->max_height;
        scene_print_message(scene, "scene is too large, changed x2 --> x1 + max_x, y2 --> y1 + max_y");
    }

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

