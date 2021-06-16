cmake_minimum_required(VERSION 3.10)

project(serve_tests)

find_package(GTest REQUIRED)

message(GTEST " " ${GTest_FOUND})

add_executable(server_test server/SessionTest.cpp)
target_link_libraries(server_test PUBLIC server ${GTEST_BOTH_LIBRARIES})