cmake_minimum_required(VERSION 3.23)
project(p4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p4
        CommonWordList.h
        p4.cpp WordCounter.h)
