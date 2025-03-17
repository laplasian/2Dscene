#ifndef OBJECTS_H
#define OBJECTS_H

#include "lib/new.h"

//Base class
typedef struct {
    const struct Class *class;
} Shape;

struct Point {
    Shape base;
    int x, y;
};

struct Hline {
    Shape base;
    int x1, x2, y;
};

struct Rect {
    Shape base;
    int x1, y1, x2, y2;
};

struct Vline {
    Shape base;
    int y1, y2, x;
};

extern const struct Class* Vline;
extern const struct Class* Rect;
extern const struct Class* Hline;
extern const struct Class* Point;

#endif //OBJECTS_H
