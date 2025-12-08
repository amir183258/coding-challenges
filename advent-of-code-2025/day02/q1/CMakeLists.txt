cmake_minimum_required(VERSION 3.10)
project(question1_2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_executable(brute_force_question1_2
    src/brute_force.cpp
)

add_executable(question1_2
    src/main.cpp
)

file(COPY ${CMAKE_SOURCE_DIR}/adventofcode.com_2025_day_2_input.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/adventofcode.com_2025_day_2_input_test.txt DESTINATION ${CMAKE_BINARY_DIR})

