cmake_minimum_required(VERSION 3.28)
project(2Dscene C)

set(CMAKE_C_STANDARD 11)

add_executable(2Dscene main.c
        lib/new.c
        lib/new.h
        lib/slist.h
        lib/slist.c
        lib/console.c
        lib/console.h
        scene.c
        scene.h
        objects.c
        objects.h
        factory.c
        factory.h
)

