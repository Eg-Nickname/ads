cmake_minimum_required(VERSION 3.10)

project(Simple CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
# file(GLOB SOURCES "src/*")
set(BENCH_SRC "src/bench/bench.cpp" "src/simple_set.cpp")


add_executable(ss_tests ${SOURCES})
add_executable(ss_bench ${BENCH_SRC})

target_compile_options(ss_tests PRIVATE
    -pedantic
    -Wall          
    -Wextra            
    -Werror
    -O3            
    -march=native
)