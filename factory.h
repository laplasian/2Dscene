//
// Created by user on 18.03.2025.
//

#ifndef FACTORY_H
#define FACTORY_H

#include "scene.h"
#include "new.h"


#define max_line_size 200
#define max_objects_size 100

struct Class * get_obj(const char * line, Scene * scene);
void * create_slist(FILE *file, Scene * scene);
void delete_obj(void * data);

#endif //FACTORY_H
