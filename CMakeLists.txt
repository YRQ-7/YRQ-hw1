cmake_minimum_required(VERSION 3.10)
project(algebra_hw1)

set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR}/inc)

file(GLOB SOURCES "src/*.c")

add_executable(main ${SOURCES})