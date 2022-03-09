cmake_minimum_required(VERSION 3.17)
project(set)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(set
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Set.cpp
        Set.h
        SetIterator.cpp
        SetIterator.h
        ShortTest.cpp
        ShortTest.h)
