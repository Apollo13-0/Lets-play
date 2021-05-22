cmake_minimum_required(VERSION 3.17)
project(Lets_play)

set(CMAKE_CXX_STANDARD 14)

include_directories(List)

add_executable(Lets_play
        Backtracking.cpp
        Backtracking.h
        main.cpp
        List/List.cpp
        List/List.h
        List/Node.cpp
        List/Node.h)
