cmake_minimum_required(VERSION 3.10)

project(solution1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(solution1
    src/main.cpp
    src/plane.cpp
    src/signalProcessor.cpp)
