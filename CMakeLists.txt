cmake_minimum_required(VERSION 3.21)

project(Lumen)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_GENERATOR_PLATFORM x64)

add_library(Lumen SHARED "Lumen/lumen.cc")

add_subdirectory(Index)
add_subdirectory(Lib)
add_subdirectory(Lumen)

target_compile_options(Lumen PUBLIC "/DNOMINMAX")


# VCPKG Libraries

find_package(ryml CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE ryml::ryml)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE fmt::fmt)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(cpr CONFIG REQUIRED)
target_link_libraries(Lumen PRIVATE cpr::cpr)


# Compiler Configuration

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("MSVC")

    # /await for winrt
    target_compile_options(Lumen PUBLIC "/await")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("GNU")

endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("Clang")

    # pointer-to-function and pointer-to-object
    target_compile_options(Lumen PUBLIC "-Wno-microsoft-cast")

    # expression result unused
    target_compile_options(Lumen PUBLIC "-Wno-unused-value")

    # non-portable Microsoft search rules
    target_compile_options(Lumen PUBLIC "-Wno-microsoft-include")

    # winrt clang error
    target_compile_options(Lumen PUBLIC "/D_SILENCE_CLANG_COROUTINE_MESSAGE")
endif ()