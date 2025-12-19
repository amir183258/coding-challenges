cmake_minimum_required(VERSION 3.10)
project(question2_9)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

add_executable(question2_9
    src/main.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/adventofcode.com_2025_day_9_input.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/adventofcode.com_2025_day_9_input_test.txt DESTINATION ${CMAKE_BINARY_DIR})
