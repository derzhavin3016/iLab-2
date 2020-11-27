cmake_minimum_required(VERSION 3.17)

project(tree)

set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(tree main.cpp)
add_executable(tree_tst main_tst.cpp)
target_compile_features(tree PRIVATE cxx_std_20)
target_compile_options(tree PRIVATE -Wall -Wextra -Wpedantic)

target_compile_features(tree_tst PRIVATE cxx_std_20)
target_compile_options(tree_tst PRIVATE -Wall -Wextra -Wpedantic)
