cmake_minimum_required(VERSION 3.16)

project(filer
    VERSION 0.1.0
    DESCRIPTION "Filesystem residue scanner"
    LANGUAGES CXX
)

# Enforce C++17 strictly
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Strong warnings for correctness
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wold-style-cast
        -Woverloaded-virtual
        -Wnon-virtual-dtor
    )
endif()

# Release defaults (correctness first, but optimized)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(filer
    src/main.cpp
    src/scanner.cpp
    src/matcher.cpp
    src/classifier.cpp
    src/aggregator.cpp
)

target_include_directories(filer PRIVATE src)