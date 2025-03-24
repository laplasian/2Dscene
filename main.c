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
        filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";
    }
    else {
        printf("args error");
        return -1;
    }

    FILE *file = fopen(filename, "r");

    Scene * scene = create_scene(file);
    void *slist = create_slist(file);

    init_scene(scene);
    draw_scene(scene, slist);

    getchar();

    delete_slist(slist);
    destroy_scene(scene);

    return 0;
}
