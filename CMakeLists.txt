cmake_minimum_required(VERSION 4.1)
project(zipprman)

set(CMAKE_CXX_STANDARD 20)

add_executable(zipprman main.cpp
        Leaf.h
        Leaf.cpp
        Tree.h
        Tree.cpp
)
