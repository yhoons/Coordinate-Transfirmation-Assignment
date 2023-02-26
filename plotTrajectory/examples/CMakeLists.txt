cmake_minimum_required(VERSION 3.24)
project(hello_cmake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(modules)

add_executable(hello_cmake main.cpp)


add_executable(exec_module2_module3 examples/exec_module2_module3.cpp)
target_link_libraries(exec_module2_module3 PRIVATE
        module2
        module3
        )