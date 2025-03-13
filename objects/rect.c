//
// Created by user on 27.02.2025.
//

#include "rect.h"
#include "scene.h"
#include <stdio.h>


static void* rect_ctor(void* _self, va_list* app) {
    struct Rect* self = _self; // предполагаем, что _self выделен под Point

    self->x1 = va_arg(*app, int);
    self->y1 = va_arg(*app, int);
    self->x2 = va_arg(*app, int);
    self->y2 = va_arg(*app, int);

    return self;
}

static void rect_draw(const void* _self) {
    const struct Rect* self = _self;
    for (int i = self->x1; i < self->x2; ++i) {
        for (int j = self->y1; j < self->y2; ++j) {
            if (i < field_width - 1 && j < field_height - 1) {
                con_charAt('*', COLOR_POINT, field_x + i, field_y + j);
            }
        }
    }
}


static const struct Class _Rect = {
    sizeof(struct Rect),
    rect_ctor,
    0,
    rect_draw,
};


const struct Class* Rect = &_Rect; // Point это указатель на структуру типа Class