cmake_minimum_required(VERSION 3.24)
project(DA1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(headers)
include_directories(src)

add_executable(DA1
        src/main.cpp headers/Menu.h src/Menu.cpp headers/Station.h src/Station.cpp src/Graph.cpp headers/Graph.h headers/Utils.h src/Utils.cpp)
