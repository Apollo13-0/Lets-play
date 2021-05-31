cmake_minimum_required(VERSION 3.17.5)
project(Server)

set(CMAKE_CXX_STANDARD 14)


# include OpenCV
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
    # Add OpenCV headers location to your include paths
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_executable(Server divideImage.h Backtracking.h Backtracking.cpp main.cpp GAPad.cpp GAPad.h GASolver.cpp GASolver.h GAChromosome.cpp GAChromosome.h Matrix.cpp Matrix.h matrixNode.cpp matrixNode.h BPGameLogic.h BPCreateObstacules.h "A* Pathfindig.h")
target_link_libraries(Server ${OpenCV_LIBS})

