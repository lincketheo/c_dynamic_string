cmake_minimum_required(VERSION 3.26)
project(dynamic_strings C)

set(CMAKE_C_STANDARD 11)
include_directories(include)
add_library(dynstr src/dynamic_strings.c)
target_include_directories(dynstr PUBLIC include)

add_executable(main main.c)
target_link_libraries(main dynstr)
