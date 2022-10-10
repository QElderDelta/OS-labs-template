set(CMAKE_C_STANDARD 11)

add_executable(lab2
        main.c
        src/parent.c
        include/utils.h src/utils.c)

target_include_directories(lab2 PRIVATE include)

add_executable(child
        src/child.c
        include/utils.h src/utils.c)

target_include_directories(child PRIVATE include)

add_dependencies(lab2 child)
