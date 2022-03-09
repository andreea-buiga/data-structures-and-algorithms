cmake_minimum_required(VERSION 3.17)
project(priority_queue)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(priority_queue
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        PriorityQueue.cpp
        PriorityQueue.h
        ShortTest.cpp
        ShortTest.h)
