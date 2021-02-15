cmake_minimum_required(VERSION 3.12)

project(tree)

set(EXECUTABLE_OUTPUT_PATH ../)

add_executable(test.o main.cpp)
add_executable(perf_tst.o main_tst.cpp)

target_compile_features(test.o PRIVATE cxx_std_20)
target_compile_options(test.o PRIVATE "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(test.o PRIVATE "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")

target_compile_features(perf_tst.o PRIVATE cxx_std_20)
target_compile_options(perf_tst.o PRIVATE "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(perf_tst.o PRIVATE "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")
