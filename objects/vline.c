//
// Created by user on 27.02.2025.
//

#include "vline.h"

#include <stdio.h>


static void* vline_ctor(void* _self, va_list* app) {
    struct Vline* self = _self; // предполагаем, что _self выделен под Point

    self->y1 = va_arg(*app, int);
    self->y2 = va_arg(*app, int);
    self->x = va_arg(*app, int);

    return self;
}

static void vline_draw(const void* _self) {
    const struct Vline* self = _self;
    printf("point at: %d %d %d", self->y1, self->y2, self->x);
}


static const struct Class _Vline = {
    sizeof(struct Vline),
    vline_ctor,
    0,
    vline_draw,
};


const struct Class* Vline = &_Vline;