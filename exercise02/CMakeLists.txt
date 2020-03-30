cmake_minimum_required(VERSION 3.15)
project(ps_os_2020 C)

set(CMAKE_C_STANDARD 99)
set(SOURCES task1.c task2.c task3.c)

add_executable(bstree_test ${SOURCES})