//
// Created by user on 27.02.2025.
//

#ifndef PARCER_H
#define PARCER_H

#include <stddef.h>

#define max_line_size 100
#define max_obgect 100

#define screen 0
#define cyrcle 1
#define rect 2
#define triangle 3
#define point 4
#define hline 5
#define vline 6

#define comp(a, b) strcmp(a, b) == 0

typedef struct Object {
    size_t type;
    size_t num_args;
    int *args;
} Object;

Object ** get_objects(const char *filename);



#endif //PARCER_H
