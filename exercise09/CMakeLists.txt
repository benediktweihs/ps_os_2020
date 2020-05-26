cmake_minimum_required(VERSION 3.15)
project(ps_os_2020 C)
find_package(Threads REQUIRED)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_C11_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(TASK1 membench.c)
set(LIB system_allocator.c)
set(TASK2 task2.c)
set(TASK3 task3.c)

add_executable(TASK1 ${TASK1})
add_executable(TASK3 ${TASK3})
add_library(system_allocator SHARED ${LIB})
add_library(task2 SHARED ${TASK2})
target_link_libraries(TASK1 task2 system_allocator ${CMAKE_DL_LIBS} Threads::Threads)
target_link_libraries(TASK3 task2 system_allocator ${CMAKE_DL_LIBS} Threads::Threads)

