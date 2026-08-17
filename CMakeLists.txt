cmake_minimum_required(VERSION 3.20)

project(RoutePlanningEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(route_engine
    src/main.cpp
    src/graph.cpp
    src/dijkstra.cpp
    src/astar.cpp
    src/gridgraph.cpp
    src/graphload.cpp
    src/benchmark.cpp
)

target_include_directories(route_engine
    PRIVATE
    include
)