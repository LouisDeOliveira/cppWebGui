cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cppwebui)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add external folder
include_directories(external)
find_package(Crow)
# Add the executable
add_subdirectory(src)