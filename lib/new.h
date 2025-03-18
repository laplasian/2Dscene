#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>
#include <stdarg.h>

struct Class {
    size_t size;
    void *(*ctor)(void *self, va_list *app);
    void *(*dtor)(void *self);
    void (*draw)(const void *self, va_list *app);
};

void *new(const void *class, ...);

void delete(void *item);

void draw(const void *self, ...);

#endif //OBJECT_H
