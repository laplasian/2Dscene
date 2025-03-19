#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "factory.h"
#include "lib/console.h"
#include "lib/slist.h"
#include "lib/new.h"

int main(int argc, char *argv[])
{
    if (argc == 0) {
        char *filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";
        char *fn = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene_img1";
        Scene * s = create_scene(filename);
    }

    Scene * s = create_scene(argv[1]);

    int max_x = 0;
    int max_y = 0;


    con_init();
    con_hideCursor();
    init_colors();

    // calculate size of field
    con_getMaxXY(&max_x, &max_y);
    field_width = max_x;
    field_height = max_y;
    // assert(field_width > 2);
    // assert(field_height > 2);

    initial_draw();

    size_t current = slist_first(s->slist);
    while (current != slist_stop(s->slist)) {
        draw(*(struct Class **)slist_current(s->slist, current), s, global_draw);
        current = slist_next(s->slist, current);
    }

    getchar();

    destroy_scene(s);
    con_clearScr();
    con_deinit();

    return 0;
}
