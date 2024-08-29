cmake_minimum_required(VERSION 3.26)
project(GG C)

set(CMAKE_C_STANDARD 11)

add_executable(GG main.c
        library/date_structurs/test_string.c
        library/date_structurs/lab_18.c
        library/algoritms/lab_19.c
)

add_subdirectory(library)
target_link_libraries(GG algoritms)
target_link_libraries(GG date_structurs)