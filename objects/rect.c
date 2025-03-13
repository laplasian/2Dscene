//
// Created by user on 27.02.2025.
//

#include "rect.h"

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
    printf("rect at: %d %d %d %d", self->x1, self->y1, self->x2, self->y2);
}


static const struct Class _Rect = {
    sizeof(struct Rect),
    rect_ctor,
    0,
    rect_draw,
};


const struct Class* Rect = &_Rect; // Point это указатель на структуру типа Class