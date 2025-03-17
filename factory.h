//
// Created by user on 18.03.2025.
//

#ifndef FACTORY_H
#define FACTORY_H

#include "scene.h"
#include "lib/new.h"


#define max_line_size 100
#define max_objects_size 100

struct Class * get_obj(const char * line);
Scene * create_scene(const char * file_name);

#endif //FACTORY_H
