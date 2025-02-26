//
// Created by user on 27.02.2025.
//

#ifndef PARCER_H
#define PARCER_H

#define screen 0
#define cyrcle 1
#define rect 2
#define triangle 3
#define point 4
#define hline 5
#define vline 6

int get_object(char *str);
int * get_args(char *str);
char * read_file(char *filename);


#endif //PARCER_H
