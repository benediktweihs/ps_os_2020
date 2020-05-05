cmake_minimum_required(VERSION 3.15)
project(ps_os_2020 C)

set(CMAKE_C_STANDARD 99)
set(SOURCES task1_server.c)
set(SOURCES_C task1_client.c)

add_executable(task1_server ${SOURCES})
add_executable(task1_client ${SOURCES_C})