cmake_minimum_required(VERSION 3.21)
project(Lumen)

set(CMAKE_CXX_STANDARD 23)

add_library(Lumen SHARED "Lumen/lumen.cc")

add_subdirectory(Index)
add_subdirectory(Lumen)