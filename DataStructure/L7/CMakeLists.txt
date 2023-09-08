cmake_minimum_required(VERSION 3.23)
project(L7)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(L7
        BST.h
        Huffman.cpp
        Huffman.h
        lab7.cpp)
