cmake_minimum_required(VERSION 3.5)

project(raystation2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB raystation2_SRC
    "*.h"
    "*.cpp"
)

add_executable(raystation2 ${raystation2_SRC})
