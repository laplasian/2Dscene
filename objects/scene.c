//
// Created by user on 13.03.2025.
//

#include "scene.h"
#include <assert.h>

#include "console.h"
#include "new.h"

int field_x = 0;
int field_y = 0;
int field_width = 0;
int field_height = 0;

/* Output char using given color pair at given position. */
void con_charAt(int ch, int color, int x, int y) {
    con_gotoXY(x, y);
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
                con_charAt(ch, color, field_x + i, field_y + j);
            }
        }
    }

}

int run(Scene* scene) {
    int max_x, max_y;
    int quit = 0;

    max_x = scene->width;
    max_y = scene->height;

    con_init();
    con_hideCursor();

    init_colors();

    // calculate size of field
    con_getMaxXY(&max_x, &max_y);

    field_x = FIELD_PADDING + TITLE_Y + 1;
    field_y = FIELD_PADDING;
    field_width = max_x - field_x - FIELD_PADDING;
    field_height = max_y - field_y - FIELD_PADDING;

    initial_draw();

    for (int i = 0; i < scene->size; ++i) {
        draw(scene->objects[i]);
    }

    while (!quit) {
        if (con_keyPressed()) {
            quit = 1;
        }
    }

    con_clearScr();
    con_deinit();
    return 0;
}

