cmake_minimum_required(VERSION 3.17)
project(dynamic_strings C)

set(CMAKE_C_FLAGS "-Wall -g")

include_directories(include)
set(CMAKE_C_STANDARD 11)
add_library(dynstr dynamic_strings.c)
target_include_directories(dynstr PUBLIC include)

add_executable(main main.c)
add_executable(test test.c)

target_link_libraries(main dynstr)
target_link_libraries(test dynstr)
