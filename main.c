#include <stdio.h>

#include "objects/imports.h"


int main(void)
{
    char *filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";

    Scene * scene = make_scene(filename);
    run(scene);

    return 0;
}
