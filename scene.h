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
    int message_count;
    int max_width, max_height;
}Scene;

Scene * create_scene(FILE *file);
void scene_draw_point(Scene * scene, int x, int y, int color, int ch);
void draw_scene(Scene * scene, const void * slist);
void scene_print_message(Scene * scene, const char * error);

void destroy_scene(Scene * scene);
void init_scene(Scene * scene);



#endif //SCENE_H
