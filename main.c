#include <stdio.h>
#include "oop/parser.h"

int main(void)
{
    char *filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";
    Object ** objects = get_objects(filename);

    return 0;
}
