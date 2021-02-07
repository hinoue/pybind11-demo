cmake_minimum_required(VERSION 2.8.12)
project(tooling)

find_package(PythonInterp REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(/usr/lib/llvm-6.0/include)
add_subdirectory(pybind11)
pybind11_add_module(tooling example.cpp)
target_link_libraries(tooling PRIVATE /usr/lib/llvm-6.0/lib/libclang.so /usr/lib/llvm-6.0/lib/libLLVM.so)
