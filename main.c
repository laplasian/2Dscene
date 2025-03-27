#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "factory.h"
#include "lib/console.h"
#include "lib/slist.h"
#include "new.h"


int main(int argc, char *argv[])
{
    char *filename;
    if (argc == 2) {
        filename = argv[1];
    } else if (argc == 1) {
        filename = "scene.txt";
    }
    else {
        printf("args error");
        return -1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("file not exist");
        return -1;
    }

    Scene * scene = create_scene(file);
    if (scene == NULL) {
        printf("create scene error");
        return -1;
    }
    init_scene(scene);

    void *slist = create_slist(file, scene);
    if (slist == NULL) {
        printf("create slist error");
        return -1;
    }
    draw_scene(scene, slist);

    while (con_getKey() != CON_KEY_ESCAPE) {
    }

    slist_destroy(slist, delete_obj);
    destroy_scene(scene);

    return 0;
}
