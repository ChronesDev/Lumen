cmake_minimum_required(VERSION 3.21)
project(Lumen)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_GENERATOR_PLATFORM x64)

add_library(Lumen SHARED "Lumen/lumen.cc")

add_subdirectory(Index)
add_subdirectory(Lib)
add_subdirectory(Lumen)

target_compile_options(Lumen PUBLIC "/DNOMINMAX" "/D_SILENCE_CLANG_COROUTINE_MESSAGE")