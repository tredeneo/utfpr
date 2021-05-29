cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
string(APPEND CMAKE_C_FLAGS "-Wunused-variable -Wall -Wpedantic")
set(CMAKE_C_STANDARD 99)
project(SO)
include_directories(${CMAKE_SOURCE_DIR}/../../include)
string(APPEND LIBS "${CMAKE_SOURCE_DIR}/../../lib")

add_executable(SO ../pingpong-contab-prio.c ../ppos-core-scheduler.c ../ppos-core-task-aux.c )

target_link_libraries(SO ${LIBS}/queue.o ${LIBS}/ppos-core-task.o ${LIBS}/ppos-core-sched.o)
