cmake_minimum_required(VERSION 3.7)
project(Window)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})

add_executable(Window src/globals.cpp src/main.cpp src/object.cpp src/window.cpp src/sprite.cpp src/inputs.cpp)
target_include_directories(Window PRIVATE include/)
target_link_libraries(Window SDL2 fmt)
