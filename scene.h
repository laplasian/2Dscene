#ifndef SCENE_H
#define SCENE_H

#define TITLE_X 1
#define TITLE_Y 1

#define FIELD_PADDING 3

#define CHAR_BORDER '#'
#define CHAR_FIELD  ' '
#define CHAR_POINT  '@'

#define COLOR_BORDER 1
#define COLOR_FIELD  2
#define COLOR_POINT  3
#include <stdio.h>

typedef struct {
    int x1, x2, y1, y2;
}Scene;

void scene_draw_point(Scene * scene, int x, int y, int color, int ch);

void clear_scene(Scene * scene);
void destroy_scene(Scene * scene);
void init_scene(Scene * scene);
Scene * create_scene(FILE *file);
void draw_scene(Scene * scene, const void * slist);

void print_message_at_scene(const char * error);

extern  int field_width;
extern int field_height;

#endif //SCENE_H
