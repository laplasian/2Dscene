#include <stdio.h>
#include "parcer.h"

int main(void)
{
    char *filename = "C:\\Users\\user\\CLionProjects\\2Dscene\\scene.txt";
    printf("%s", read_file(filename));
    return 0;
}
