cmake_minimum_required(VERSION 3.12)

project(tree)

set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(tree.o main.cpp)
add_executable(tree_tst.o main_tst.cpp)
target_compile_features(tree.o PRIVATE cxx_std_20)
target_compile_options(tree.o PRIVATE -Wall -Wextra -Wpedantic)

target_compile_features(tree_tst.o PRIVATE cxx_std_20)
target_compile_options(tree_tst.o PRIVATE -Wall -Wextra -Wpedantic)
