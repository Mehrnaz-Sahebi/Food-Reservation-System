cmake_minimum_required(VERSION 3.25)
project(FOPProject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(FOPProject
        src/database.c
        src/database.h
        src/shell.c
        src/sqlite3.c
        src/sqlite3.h
        src/structures.h
        functions.c
        functions.h
        main.c
        Pages.c
        Pages.h
        testcase_processor.c
        testcase_processor.h)
