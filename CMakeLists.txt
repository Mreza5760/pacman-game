# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and language standard
project(Pacman C)
set(CMAKE_C_STANDARD 23)

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Enable static linking for Raylib and other libraries
set(BUILD_SHARED_LIBS OFF)

# Find the Raylib package (ensure it's compiled with static support)
find_package(raylib REQUIRED CONFIG)

# Collect all .c files from the src directory
file(GLOB SOURCES src/*.c)

# Define the executable and link Raylib
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib statically and ensure compatibility
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Windows-specific configurations for standalone .exe
if(WIN32)
    # Add necessary libraries for Windows
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)

    # Optional: Set compiler flags for static runtime
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Debugging and status messages
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Raylib: Found at ${raylib_DIR}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Copy necessary files (e.g., assets) to the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
    COMMENT "Copying assets to build directory"
)
