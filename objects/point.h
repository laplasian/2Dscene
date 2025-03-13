//
// Created by user on 27.02.2025.
//

#ifndef POINT_H
#define POINT_H

#include "Shape.h"

struct Point {
  Shape base;
  int x, y;
};

extern const struct Class* Point;

#endif //POINT_H
