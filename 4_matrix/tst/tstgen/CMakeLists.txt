cmake_minimum_required(VERSION 3.13)

project(gentst)

add_executable(gen gen.cpp)

target_compile_features(matrix PRIVATE cxx_std_20)
target_compile_options(matrix PRIVATE -Wall -Wextra -Wpedantic)