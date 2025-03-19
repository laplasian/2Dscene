#include "objects.h"
#include <stdio.h>

#include "scene.h"

/*
 * Class Point description
 */

static void* point_ctor(void* _self, va_list* app) {
    struct Point* self = _self; // предполагаем, что _self выделен под Point

    self->x = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void point_draw(const void* _self, va_list *app) {
    const struct Point* self = _self;
    Scene * scene = va_arg(*app, Scene*);
    if (scene->x1 <= self->x <= scene->x2 && scene->y1 <= self->y <= scene->y2) {
        void (*_global_draw)(int ch, int color, int x, int y) = va_arg(*app, void (*)(int ch, int color, int x, int y));
        _global_draw('*', COLOR_POINT, self->x, self->y);
    }
}

/*
 * Class Hline description
 */

static void* hline_ctor(void* _self, va_list* app) {
    struct Hline* self = _self; // предполагаем, что _self выделен под Hline

    self->x1 = va_arg(*app, int);
    self->x2 = va_arg(*app, int);
    self->y = va_arg(*app, int);

    return self;
}

static void hline_draw(const void* _self, va_list *app) {
    const struct Hline* self = _self;
    Scene * scene = va_arg(*app, Scene*);
    void (*_global_draw)(int ch, int color, int x, int y) = va_arg(*app, void (*)(int ch, int color, int x, int y));

    for (int i = self->x1; i < self->x2; ++i) {
        if (scene->x1 <= i <= scene->x2 && scene->y1 <= self->y <= scene->y2) _global_draw('-', COLOR_POINT, i, self->y);
    }
}

/*
 * Class Vline description
 */

static void* vline_ctor(void* _self, va_list* app) {
    struct Vline* self = _self; // предполагаем, что _self выделен под Point

    self->y1 = va_arg(*app, int);
    self->y2 = va_arg(*app, int);
    self->x = va_arg(*app, int);

    return self;
}

static void vline_draw(const void* _self, va_list *app) {
    const struct Vline* self = _self;

    Scene * scene = va_arg(*app, Scene*);
    void (*_global_draw)(int ch, int color, int x, int y) = va_arg(*app, void (*)(int ch, int color, int x, int y));

    for (int i = self->y1; i < self->y2; ++i) {
        if (scene->x1 <= self->x <= scene->x2 && scene->y1 <= i <= scene->y2) _global_draw('|', COLOR_POINT, self->x, i);
    }
}

/*
 * Class Rect description
 */

static void* rect_ctor(void* _self, va_list* app) {
    struct Rect* self = _self; // предполагаем, что _self выделен под Point

    self->x1 = va_arg(*app, int);
    self->y1 = va_arg(*app, int);
    self->x2 = va_arg(*app, int);
    self->y2 = va_arg(*app, int);

    return self;
}

static void rect_draw(const void* _self, va_list *app) {
    const struct Rect* self = _self;
    Scene * scene = va_arg(*app, Scene*);
    void (*_global_draw)(int ch, int color, int x, int y) = va_arg(*app, void (*)(int ch, int color, int x, int y));

    for (int i = self->x1; i < self->x2; ++i) {
        if (scene->x1 <= i <= scene->x2 && scene->y1 <= self->y1 <= scene->y2) _global_draw('-', COLOR_POINT, i, self->y1);
        if (scene->x1 <= i <= scene->x2 && scene->y1 <= self->y2 <= scene->y2) _global_draw('-', COLOR_POINT, i, self->y2);
    }
    for (int j = self->y1; j < self->y2; ++j) {
        if (scene->x1 <= self->x1 <= scene->x2 && scene->y1 <= j <= scene->y2) _global_draw('|', COLOR_POINT, self->x1, j);
        if (scene->x1 <= self->x2 <= scene->x2 && scene->y1 <= j <= scene->y2) _global_draw('|', COLOR_POINT, self->x2, j);
    }
}

/*
 * Class constructing
 */

static const struct Class _Rect = {
    sizeof(struct Rect),
    rect_ctor,
    0,
    rect_draw,
};

static const struct Class _Vline = {
    sizeof(struct Vline),
    vline_ctor,
    0,
    vline_draw,
};

static const struct Class _Hline = {
    sizeof(struct Hline),
    hline_ctor,
    0,
    hline_draw,
};

static const struct Class _Point = {
    sizeof(struct Point),
    point_ctor,
    0,
    point_draw,
};

/*
 * Extern class description
 */

const struct Class* Point = &_Point;
const struct Class* Hline = &_Hline;
const struct Class* Vline = &_Vline;
const struct Class* Rect = &_Rect;