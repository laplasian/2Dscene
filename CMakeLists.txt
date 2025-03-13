cmake_minimum_required(VERSION 3.28)
project(2Dscene C)

set(CMAKE_C_STANDARD 11)

add_executable(2Dscene main.c
        objects/parser.h
        objects/rect.c
        objects/rect.h
        objects/point.c
        objects/point.h
        objects/vline.c
        objects/vline.h
        objects/hline.c
        objects/hline.h
        objects/parser.c
        objects/new.c
        objects/new.h
        objects/Shape.c
        objects/Shape.h
        factory.c
        factory.h
        console.c
        console.h
)
