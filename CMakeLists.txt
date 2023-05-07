cmake_minimum_required(VERSION 3.24)
project(CourseworkSecondCourse)

set(CMAKE_CXX_STANDARD 17)

include_directories(Code)

add_executable(CourseworkSecondCourse
        main.cpp
        Code/SkipList.h
        Code/AVLTree.h Testing/TestContainer.h Testing/Utils.cpp Testing/TestManager.h)