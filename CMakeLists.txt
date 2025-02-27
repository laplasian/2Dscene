cmake_minimum_required(VERSION 3.28)
project(2Dscene C)

set(CMAKE_C_STANDARD 11)

add_executable(2Dscene main.c
        oop/parser.h
        objects/cyrcle.c
        objects/cyrcle.h
        objects/rect.c
        objects/rect.h
        objects/triangle.c
        objects/triangle.h
        objects/point.c
        objects/point.h
        objects/vline.c
        objects/vline.h
        objects/hline.c
        objects/hline.h
        oop/parser.c
        oop/object.c
        oop/object.h
)
