//
// Created by user on 27.02.2025.
//

#ifndef VLINE_H
#define VLINE_H

#include "Shape.h"

struct Vline {
    Shape base;
    int y1, y2, x;
};

extern const struct Class* Vline;

#endif //VLINE_H
