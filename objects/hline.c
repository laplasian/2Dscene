//
// Created by user on 27.02.2025.
//

#include "hline.h"

#include <stdio.h>
#include "scene.h"


static void* hline_ctor(void* _self, va_list* app) {
    struct Hline* self = _self; // предполагаем, что _self выделен под Hline

    self->x1 = va_arg(*app, int);
    self->x2 = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void hline_draw(const void* _self) {
    const struct Hline* self = _self;
    for (int i = self->x1; i < self->x2; ++i) {
        if (i < field_width - 1 && self->y < field_height - 1) {
            con_charAt('*', COLOR_POINT, field_x + i, field_y + self->y);
        }
    }
}

static const struct Class _Hline = {
    sizeof(struct Hline),
    hline_ctor,
    0,
    hline_draw,
};


const struct Class* Hline = &_Hline; // это указатель на структуру типа Class