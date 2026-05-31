cmake_minimum_required(VERSION 3.16)

project(ini_parser LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(INI_PARSER_BUILD_TESTS "Build test programs" OFF)

add_library(ini_parser STATIC
    src/ini.c
)

target_include_directories(ini_parser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(INI_PARSER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
