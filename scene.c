//
// Created by user on 13.03.2025.
//

#include "scene.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include "lib/console.h"
#include "lib/new.h"
#include "lib/slist.h"

extern int field_width = 0;
extern int field_height = 0;

/* Output char using given color pair at given position. */
void global_draw(int ch, int color, int x, int y) {
    con_gotoXY(x , y);
    con_setColor((short)color);
    con_outTxt("%c", ch);
}

void init_colors() {
    con_initPair(COLOR_BORDER, CON_COLOR_BLACK, CON_COLOR_BLACK);
    con_initPair(COLOR_FIELD, CON_COLOR_GREEN, CON_COLOR_BLACK);
    con_initPair(COLOR_POINT, CON_COLOR_RED, CON_COLOR_BLACK);
}

void initial_draw() {
    con_clearScr();
    con_gotoXY(TITLE_X, TITLE_Y);

    {
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
                global_draw(ch, color,  i, j);
            }
        }
    }

}

void clear_scene(Scene * scene) {
    slist_clear(scene->slist, delete); // вызывает delete для каждого объекта
}

void destroy_scene(Scene * scene) {
    slist_destroy(scene->slist, delete);
    free(scene);
}