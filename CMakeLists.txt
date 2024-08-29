cmake_minimum_required(VERSION 3.26)
project(GG C)

set(CMAKE_C_STANDARD 11)

add_executable(GG main.c)

add_subdirectory(library)
target_link_libraries(GG algoritms)
target_link_libraries(GG date_structurs)