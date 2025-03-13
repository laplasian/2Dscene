//
// Created by user on 27.02.2025.
//

#ifndef RECT_H
#define RECT_H


#include "Shape.h"

struct Rect {
    Shape base;
    int x1, y1, x2, y2;
};

extern const struct Class* Rect;

#endif //RECT_H
