#include <stdio.h>

#include "factory.h"
#include "objects/parser.h"
#include "objects/vline.h"
#include "objects/new.h"

int main(void)
{
    char *filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";

    //const struct Class *p = new(Vline, 10, 10, 100);

    //run();

    struct Class * objects = get_objects(filename);

    return 0;
}
