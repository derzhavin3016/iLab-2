cmake_minimum_required(VERSION 3.17)

project(tree)

set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(tree main.cpp)
target_compile_features(tree PRIVATE cxx_std_20)
target_compile_options(tree PRIVATE -Wall -Wextra -Wpedantic)
