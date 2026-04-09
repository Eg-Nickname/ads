cmake_minimum_required(VERSION 3.10)

project(Zestaw2 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# file(GLOB A_SOURCES "src/A/*.cpp")
file(GLOB B_SOURCES "src/B/*.cpp")

# add_executable(A_TASK ${A_SOURCES})
add_executable(B_TASK "B/main.cpp")

# target_compile_options(A_TASK PRIVATE
#     -pedantic
#     -Wall          
#     # -Wextra            
#     # -Werror
#     -O3            
#     -march=native
# )

target_compile_options(B_TASK PRIVATE
    -pedantic
    -Wall          
    # -Wextra            
    # -Werror
    -O3            
    -march=native
)