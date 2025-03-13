//
// Created by user on 13.03.2025.
//

#include "factory.h"
#include <assert.h>
#include "console.h"

#define TITLE_X 3
#define TITLE_Y 1

#define FIELD_PADDING 3

#define CHAR_BORDER '#'
#define CHAR_FIELD  ' '
#define CHAR_POINT  '@'

#define COLOR_BORDER 1
#define COLOR_FIELD  2
#define COLOR_POINT  3

static int field_x, field_y; // top-left corner
static int field_width, field_height;
static int point_x, point_y;

/* Output char using given color pair at given position. */
static void con_charAt(int ch, int color, int x, int y) {
    con_gotoXY(x, y);
    con_setColor((short)color);
    con_outTxt("%c", ch);
}

static void init_colors() {
    con_initPair(COLOR_BORDER, CON_COLOR_BLACK, CON_COLOR_BLUE);
    con_initPair(COLOR_FIELD, CON_COLOR_GREEN, CON_COLOR_GREEN);
    con_initPair(COLOR_POINT, CON_COLOR_RED, CON_COLOR_GREEN);
}

static void initial_draw() {
    con_clearScr();
    con_gotoXY(TITLE_X, TITLE_Y);
    con_outTxt("Use arrows to move point, use Esc to exit.");

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

    point_x = field_x + field_width/2;
    point_y = field_y + field_height/2;
    con_charAt(CHAR_POINT, COLOR_POINT, point_x, point_y);
}

int run() {
    int max_x, max_y;

    con_init();
    con_hideCursor();

    init_colors();

    // calculate size of field
    con_getMaxXY(&max_x, &max_y);
    field_x = FIELD_PADDING + TITLE_Y + 1;
    field_y = FIELD_PADDING;
    field_width = max_x - field_x - FIELD_PADDING;
    field_height = max_y - field_y - FIELD_PADDING;
    // assert(field_width > 2);
    // assert(field_height > 2);

    initial_draw();

    con_clearScr();
    con_deinit();
    return 0;
}

