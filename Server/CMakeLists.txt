cmake_minimum_required(VERSION 3.17.5)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server main.cpp Matrix.cpp Matrix.h matrixNode.cpp matrixNode.h BPGameLogic.h BPCreateObstacules.h "A* Pathfindig.h")