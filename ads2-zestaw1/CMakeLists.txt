cmake_minimum_required(VERSION 3.10)

project(ListSet CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(tests ${SOURCES})

target_compile_options(tests PRIVATE
    -pedantic
    -Wall          
    -Wextra            
    -Werror
    -O3            
    -march=native
)