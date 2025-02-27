cmake_minimum_required(VERSION 3.28)
project(2Dscene C)

set(CMAKE_C_STANDARD 11)

add_executable(2Dscene main.c
        new.c
        new.h
        object.h
        cyrcle.c
        cyrcle.h
        rect.c
        rect.h
        triangle.c
        triangle.h
        point.c
        point.h
        vline.c
        vline.h
        hline.c
        hline.h
        object.c
)
