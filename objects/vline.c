//
// Created by user on 27.02.2025.
//

#include "vline.h"

#include <stdio.h>
#include "scene.h"

static void* vline_ctor(void* _self, va_list* app) {
    struct Vline* self = _self; // предполагаем, что _self выделен под Point

    self->y1 = va_arg(*app, int);
    self->y2 = va_arg(*app, int);
    self->x = va_arg(*app, int);

    return self;
}

static void vline_draw(const void* _self) {
    const struct Vline* self = _self;
    for (int i = self->y1; i < self->y2; ++i) {
        if (self->x < field_width - 1 && i < field_height - 1) {
            con_charAt('*', COLOR_POINT, field_x + self->x, field_y + i);
        }
    }
}


static const struct Class _Vline = {
    sizeof(struct Vline),
    vline_ctor,
    0,
    vline_draw,
};


const struct Class* Vline = &_Vline;