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

typedef struct {
    int x1, x2, y1, y2;
    void * slist;
}Scene;

int run(Scene* scene);
void con_charAt(int ch, int color, int x, int y);

#endif //SCENE_H
