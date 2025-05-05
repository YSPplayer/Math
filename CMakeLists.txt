cmake_minimum_required(VERSION 3.31)
project(Math)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON) #必须要求编译器支持cmake版本，否则报错
aux_source_directory(Math SRC_LIST) #收集math目录下(不递归)所有的cpp文件到SRC_LIST
add_executable(Math ${SRC_LIST}
        Math/Geometry/point.cpp
        Math/Geometry/point.h
        Math/object.cpp
        Math/object.h)