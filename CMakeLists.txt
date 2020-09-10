cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(sincos VERSION 1.0)

# C++ setting 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic -Werror -O2)

# google benchmark 
add_subdirectory(benchmark)

add_library(sincoslib SHARED
    sincos.cxx
    ATLASCxxUtils.h
)

add_executable(sincos sincos.cxx)
add_executable(sincos_bench sincos_bench.cxx)

target_link_libraries(sincos benchmark)
target_link_libraries(sincos_bench sincoslib benchmark)

