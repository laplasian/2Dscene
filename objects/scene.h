#ifndef FACTORY_H
#define FACTORY_H

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
    int size;
    int capacity;
    struct Class ** objects;
    int width;
    int height;
}Scene;

int run(Scene* scene);
void con_charAt(int ch, int color, int x, int y);

extern int field_x, field_y; // top-left corner
extern int field_width, field_height;

#endif //FACTORY_H
