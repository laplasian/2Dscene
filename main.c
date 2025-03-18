#include <assert.h>
#include <stdio.h>
#include "factory.h"
#include "lib/slist.h"
#include "lib/new.h"

typedef struct {
    int array[8];
    float d_variable;
} Value;

int main(void)
{
    char *filename = "scene.txt";
    Scene * s = create_scene(filename);

    size_t current = slist_first(s->slist);

    while (current != slist_stop(s->slist)) {
        draw(slist_current(s->slist, current));
        current = slist_next(s->slist, current);
    }

    return 0;
}
