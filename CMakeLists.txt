cmake_minimum_required(VERSION 3.24)
project(CourseworkSecondCourse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-v")

include_directories(Code)

add_executable(CourseworkSecondCourse
        Code/main.cpp
        Code/SkipList.h
        Code/AVLTree.h)