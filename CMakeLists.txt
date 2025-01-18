cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PongCLI)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the output directory for build files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/target)

# Add the include directory
include_directories(include)

# Add the executable
add_executable(pong-cli
    src/main.cpp
    src/input.cpp
)
