cmake_minimum_required(VERSION 3.5)

project(raystation2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB raystation2_SRC
    "*.h"
    "*.cpp"
)

add_executable(raystation2 ${raystation2_SRC})

if (CMAKE_C_COMPILER MATCHES "mips64r5900el-ps2-elf-gcc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -ffast-math")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")
    set(USE_VU false)

    add_definitions(-D_EE)

    if (USE_VU)
        add_definitions(-DUSE_VU)
    endif()

    include_directories(-I$ENV{PS2SDK}/ee/include -I$ENV{PS2SDK}/common/include -I$ENV{PS2SDK}/ports/include -I$ENV{PS2DEV}/gsKit/include)

    target_link_directories(raystation2 PRIVATE -L$ENV{PS2SDK}/ee/lib -L$ENV{PS2SDK}/ports/lib -L$ENV{PS2DEV}/gsKit/lib)
    target_link_libraries(raystation2 PRIVATE -lgskit -ldmakit)

    set_target_properties(raystation2 PROPERTIES SUFFIX .elf)
endif()
