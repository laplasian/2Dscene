//
// Created by user on 27.02.2025.
//

#include "point.h"

#include <stdarg.h>
#include <stdio.h>

#include "new.h"


static void* point_ctor(void* _self, va_list* app) {
    struct Point* self = _self;

    self->_class = va_arg(*app, void*);
    self->x = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void point_draw(const void* _self) {
    const struct Point* self = _self;
    printf("point at: (%d,%d)\n", self->x, self->y);
}


static const struct Class _Point = {
    // Размер структуры данных объекта
    sizeof(struct Point),
    // Указатель на функцию-конструктор
    point_ctor,
    // Деструктор отсутствует
    0,
    // Указатель на виртуальную функцию draw
    point_draw,
};


const void* Point = &_Point; // Point это указатель на структуру типа Class