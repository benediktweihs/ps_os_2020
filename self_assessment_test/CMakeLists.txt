cmake_minimum_required(VERSION 3.15)
project(ps_os_2020 C)

set(CMAKE_C_STANDARD 99)
set(SOURCES bstree.c bstree_test.c bstree.h ../exercise05/task1_a.c ../exercise05/task1_b.c)

add_executable(ps_os_2020 ${SOURCES})