cmake_minimum_required(VERSION 3.10)
project(random-cpp-stuff)

add_library(
    random-cpp-stuff
    INTERFACE
)

target_include_directories(
    random-cpp-stuff
    INTERFACE
    include/
)

target_compile_features(
    random-cpp-stuff
    INTERFACE
    cxx_std_17
)

add_subdirectory(tests)