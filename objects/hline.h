//
// Created by user on 27.02.2025.
//

#ifndef HLINE_H
#define HLINE_H

#include "Shape.h"

struct Hline {
    Shape base;
    int x1, x2, y;
};

extern const struct Class* Hline;

#endif //HLINE_H
