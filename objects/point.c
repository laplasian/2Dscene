//
// Created by user on 27.02.2025.
//

#include "point.h"
#include <stdio.h>

#include "scene.h"


static void* point_ctor(void* _self, va_list* app) {
    struct Point* self = _self; // предполагаем, что _self выделен под Point

    self->x = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void point_draw(const void* _self) {
    const struct Point* self = _self;
    con_charAt('*', COLOR_POINT, self->x, self->y);
}


static const struct Class _Point = {
    sizeof(struct Point),
    point_ctor,
    0,
    point_draw,
};


const struct Class* Point = &_Point; // Point это указатель на структуру типа Class