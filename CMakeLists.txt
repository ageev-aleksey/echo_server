cmake_minimum_required(VERSION 3.10)

project(conan_example)

include(cmake/utils.cmake)
conan_init()

option(BUILD_TEST "will build test (gtest required)" ON)

add_subdirectory(src)

if(${BUILD_TEST})
    add_subdirectory(tests)
endif()