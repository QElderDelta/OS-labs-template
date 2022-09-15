set(CMAKE_C_STANDARD 11)

add_executable(lab1
        main.c
        src/parent.c
        include/utils.h src/utils.c)

target_include_directories(lab1 PRIVATE include)

add_executable(child
        src/child.c
        include/utils.h src/utils.c)

target_include_directories(child PRIVATE include)

add_dependencies(lab1 child)
