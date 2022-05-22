cmake_minimum_required(VERSION 3.22)
project(DA_TP2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(DA_TP2 main.cpp Graph.cpp Graph.h Database.cpp Database.h)
