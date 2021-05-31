cmake_minimum_required(VERSION 3.17.5)
project(Server)

set(CMAKE_CXX_STANDARD 14)


add_executable(Backtracking.h Backtracking.cpp main.cpp GAPad.cpp GAPad.h GASolver.cpp GASolver.h GAChromosome.cpp GAChromosome.h Matrix.cpp Matrix.h matrixNode.cpp matrixNode.h BPGameLogic.h BPCreateObstacules.h "A* Pathfindig.h")

