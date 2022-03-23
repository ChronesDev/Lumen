cmake_minimum_required(VERSION 3.21)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(Lumen)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_GENERATOR_PLATFORM x64)

add_library(Lumen SHARED "Lumen/lumen.cc")

add_subdirectory(Index)
add_subdirectory(Lib)
add_subdirectory(Lumen)

target_compile_options(Lumen PUBLIC "/DNOMINMAX" "/D_SILENCE_CLANG_COROUTINE_MESSAGE")

# VCPKG Libraries

find_package(ryml CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE ryml::ryml)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE fmt::fmt)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(cpr CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE cpr::cpr)