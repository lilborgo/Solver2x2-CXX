cmake_minimum_required(VERSION 3.22)
project(Solver2x2_CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(Solver2x2 STATIC
        src/Coords.h
        src/Coords.cpp
        src/move.cpp
        src/move.h
        src/Explore.cpp
        src/Explore.h
        src/Tiles.cpp
        src/Tiles.h
        src/Solver2x2.cpp)

add_executable(example
        example.cpp  )

target_link_libraries(example Solver2x2)
