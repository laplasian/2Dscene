#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>
#include <stdarg.h>
#include "scene.h"

struct Class {
    size_t size;
    void *(*ctor)(void *self, va_list *app);
    void *(*dtor)(void *self);
    void (*draw)(const void *self, Scene *scene);
};

void *new(const void *class, ...);

void delete(void *item);

void draw(const void *self, Scene* scene);

#endif //OBJECT_H
