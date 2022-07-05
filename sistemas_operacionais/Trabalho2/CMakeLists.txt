cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
string(APPEND CMAKE_C_FLAGS "-Wunused-variable -Wall")
set(CMAKE_C_STANDARD 99)
project(SO)

add_executable(SO ./ppos_disk.c)

target_link_libraries(SO ${CMAKE_SOURCE_DIR}/pingpong-disco2.o ${CMAKE_SOURCE_DIR}/ppos-core-task-aux.o ${CMAKE_SOURCE_DIR}/disk.o ${CMAKE_SOURCE_DIR}/queue.o ${CMAKE_SOURCE_DIR}/ppos-all.o rt)

