cmake_minimum_required(VERSION 3.15)
project(ps_os_2020 C)

set(CMAKE_C_STANDARD 99)
set(SOURCES ../exercise02/task1.c ../exercise02/task2.c ../exercise02/task3.c)

add_executable(bstree_test ${SOURCES})