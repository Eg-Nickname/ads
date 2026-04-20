cmake_minimum_required(VERSION 3.10)

project(Zestaw2 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB A_SOURCES "src/*.cpp")

add_executable(A_TASK ${A_SOURCES})

target_compile_options(A_TASK PRIVATE
    -pedantic
    -Wall          
    # -Wextra            
    # -Werror
    -O3            
    -march=native
)