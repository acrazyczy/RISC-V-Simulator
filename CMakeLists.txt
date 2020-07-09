cmake_minimum_required(VERSION 3.10.2)
project(code)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g")
include_directories(
        source
)
set(src_dir
        source/main.cpp source/simulator.cpp source/simulator.hpp source/memory.cpp source/memory.hpp source/register_manager.cpp source/register_manager.hpp source/ISA_base.hpp source/ISA.cpp source/ISA.hpp source/inc.hpp source/inc.cpp source/ALU.cpp source/ALU.hpp)
add_executable(code ${src_dir})