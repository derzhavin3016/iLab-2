cmake_minimum_required(VERSION 3.13)

project(matrix)

#find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)


set(EXECUTABLE_OUTPUT_PATH ../)
add_subdirectory(/usr/src/googletest gtest)
add_executable(matr.o main.cpp)
#add_executable(mtst.o test.cpp)

target_compile_features(matr.o PRIVATE cxx_std_20)
target_compile_options(matr.o PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_features(mtst.o PRIVATE cxx_std_20)
#target_compile_options(mtst.o PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_options(matrix PRIVATE "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
#target_include_directories(mtst.o PRIVATE ../include ${GTEST_INCLUDE_DIRS})

#target_link_libraries(mtst.o ${GTEST_LIBRARIES} Threads::Threads)

#enable_testing()
