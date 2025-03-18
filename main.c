#include <assert.h>
#include <stdio.h>
#include "factory.h"
#include "lib/console.h"
#include "lib/slist.h"
#include "lib/new.h"

typedef struct {
    int array[8];
    float d_variable;
} Value;

int main(void)
{
    char *filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";
    Scene * s = create_scene(filename);

    con_init();
    init_colors();
    con_hideCursor();

    size_t current = slist_first(s->slist);

    while (current != slist_stop(s->slist)) {
        draw(slist_current(s->slist, current), s, global_draw);
        current = slist_next(s->slist, current);
    }

    int quit = 0;
    while (!quit) {
        if (con_keyPressed()) {
            quit = 1;
        }
    }

    con_clearScr();
    con_deinit();

    return 0;
}
