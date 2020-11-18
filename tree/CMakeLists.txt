cmake_minimum_required(VERSION 3.17)

project(tree)

#find_package(GTest REQUIRED)
# find_package(Threads REQUIRED)

# include_directories(../include ${GTEST_INCLUDE_DIRS})
# add_subdirectory(/usr/src/googletest gtest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")


add_executable(tree main.cpp Tree.ii Tree.hpp Node.ii Node.hpp Tree_it.hpp Tree_it.ii)

#target_link_libraries(matrix ${GTEST_LIBRARIES} Threads::Threads)

# enable_testing()