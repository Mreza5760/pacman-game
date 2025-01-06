cmake_minimum_required(VERSION 3.10)
project(pacman-game C)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Find raylib package
find_package(raylib REQUIRED)

# Collect all source files from the src folder
file(GLOB SOURCES src/*.c)

# Specify output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the raylib library
target_link_libraries(${PROJECT_NAME} raylib)