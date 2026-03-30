cmake_minimum_required(VERSION 3.10)

project(ListSet CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB B_SOURCES "src/B/*.cpp")
# file(GLOB D_SOURCES "src/D/*.cpp")


add_executable(b_task ${B_SOURCES})
add_executable(b_bench "src/B/benchmark/bench.cpp" "src/B/list_set.cpp")

add_executable(d_task "src/D/string_set_test.cpp")
add_executable(d_bench "src/D/benchmark/bench.cpp")


target_compile_options(b_task PRIVATE
    -pedantic
    -Wall          
    -Wextra            
    -Werror
    -O3            
    -march=native
)