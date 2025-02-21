# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MicromouseSimulation)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Add the executable
add_executable(MicromouseSimulation
    src/main.cpp
    src/mouse.cpp
    src/mouse.h
    src/maze.cpp
    src/maze.h
    src/utils/logger.cpp
    src/utils/logger.h
)

# Find and link required libraries (e.g., Qt)
# find_package(Qt5 REQUIRED COMPONENTS Widgets)
# target_link_libraries(MicromouseSimulation Qt5::Widgets)

# Optionally, add any additional configurations or settings here.