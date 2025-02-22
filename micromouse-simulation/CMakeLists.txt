# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MicromouseSimulation)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Add the executable
add_executable(MicromouseSimulation
        src/main.cpp
        src/mouse.cpp
        src/maze.cpp
)