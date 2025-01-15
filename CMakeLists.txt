# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and language standard
project(Pacman C)
set(CMAKE_C_STANDARD 23)

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Find the Raylib package (installed system-wide via pacman)
find_package(raylib REQUIRED)

# Collect all .c files from the src directory
file(GLOB SOURCES src/*.c)

# Define the executable and link Raylib
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib to the project
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Optional: Additional settings for linking and debug info
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Raylib: Found at ${raylib_DIR}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")