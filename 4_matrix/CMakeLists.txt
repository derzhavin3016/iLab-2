cmake_minimum_required(VERSION 3.13)

project(matrix)

#find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)


#set(EXECUTABLE_OUTPUT_PATH ../)
#add_subdirectory(/usr/src/googletest gtest)
add_executable(matrix main.cpp)
#add_executable(matrix test.cpp)

target_compile_features(matrix PRIVATE cxx_std_20)
target_compile_options(matrix PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_options(matrix PRIVATE "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
#target_include_directories(matrix PRIVATE ../include ${GTEST_INCLUDE_DIRS})

#target_link_libraries(matrix ${GTEST_LIBRARIES} Threads::Threads)

enable_testing()
