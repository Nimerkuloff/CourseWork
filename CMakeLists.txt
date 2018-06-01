cmake_minimum_required(VERSION 3.4)
project(RGZLang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Matrix.h  Matrix.cpp main.cpp menu.cpp menu.h DList.h DNode.h  list.h)
add_executable(RGZLang ${SOURCE_FILES})