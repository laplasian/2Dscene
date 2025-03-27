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

static void point_draw(const void* _self, Scene * scene) {
    const struct Point* self = _self;

    scene_draw_point(scene, self->x, self->y, COLOR_POINT, '*');
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

static void hline_draw(const void* _self, Scene * scene) {
    const struct Hline* self = _self;

    for (int i = self->x1; i < self->x2; ++i) {
        scene_draw_point(scene,  i, self->y,COLOR_POINT,  '-');
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

static void vline_draw(const void* _self, Scene * scene) {
    const struct Vline* self = _self;

    for (int i = self->y1; i < self->y2; ++i) {
        scene_draw_point(scene,  self->x, i, COLOR_POINT, '|');
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

static void rect_draw(const void* _self, Scene * scene) {
    const struct Rect* self = _self;

    for (int i = self->x1; i < self->x2; ++i) {
        scene_draw_point(scene,  i, self->y1, COLOR_POINT, '-');
        scene_draw_point(scene,  i, self->y2,COLOR_POINT, '-');
    }
    for (int j = self->y1; j < self->y2; ++j) {
        scene_draw_point(scene,  self->x1, j,COLOR_POINT,  '|');
        scene_draw_point(scene,  self->x2, j, COLOR_POINT, '|');
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