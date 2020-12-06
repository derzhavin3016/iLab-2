cmake_minimum_required(VERSION 3.13)

project(matrix)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


set(EXECUTABLE_OUTPUT_PATH ../)
add_subdirectory(/usr/src/googletest gtest)
add_executable(matr main.cpp)
add_executable(mtst test.cpp)

target_compile_features(matr PRIVATE cxx_std_20)
target_compile_options(matr PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(mtst PRIVATE cxx_std_20)
target_compile_options(mtst PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_options(matrix PRIVATE "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
target_include_directories(mtst PRIVATE ../include ${GTEST_INCLUDE_DIRS})

target_link_libraries(mtst ${GTEST_LIBRARIES} Threads::Threads)

enable_testing()
