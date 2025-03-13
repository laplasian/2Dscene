//
// Created by user on 27.02.2025.
//

#include "hline.h"

#include <stdio.h>


static void* hline_ctor(void* _self, va_list* app) {
    struct Hline* self = _self; // предполагаем, что _self выделен под Hline

    self->x1 = va_arg(*app, int);
    self->x2 = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void hline_draw(const void* _self) {
    const struct Hline* self = _self;
    printf("point at: %d %d", self->x1, self->x2);
}


static const struct Class _Hline = {
    sizeof(struct Hline),
    hline_ctor,
    0,
    hline_draw,
};


const struct Class* Hline = &_Hline; // это указатель на структуру типа Class