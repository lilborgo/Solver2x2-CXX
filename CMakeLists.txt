cmake_minimum_required(VERSION 3.22)
project(Solver2x2_CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Solver2x2_CXX
        src/Coords.h
        src/Coords.cpp
        src/move.cpp
        src/move.h
        src/Explore.cpp
        src/Explore.h
        src/Tiles.cpp
        src/Tiles.h
        main.cpp src/Solver2x2.cpp include/Solver2x2.h)
