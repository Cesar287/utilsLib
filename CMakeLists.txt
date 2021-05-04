cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "utils")

project(${PROJECT_NAME} VERSION 1.0)

set(SOURCE_FOLDER "src")

set(HEADER_FOLDER "include")


file(GLOB_RECURSE SOURCE_FILES "${SOURCE_FOLDER}/*.cpp" "${SOURCE_FOLDER}/*.h" "${HEADER_FOLDER}/*.h")


add_library(${PROJECT_NAME} STATIC
    "${SOURCE_FILES}" src/ThWrap.cpp src/ThWrap.h)

message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

















