# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and language standard
project(Pacman C)
set(CMAKE_C_STANDARD 23)

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Enable static linking for Raylib and other libraries
set(BUILD_SHARED_LIBS OFF)

# Find the Raylib package 
find_package(raylib REQUIRED CONFIG)

# Explicitly list all source files 
set(SOURCES
    src/main.c
    src/map.c
    src/menu.c
    src/draw.c
    src/ghost.c
    src/player.c
    src/record.c
    src/embedded_loader.c
    src/embedded_assets.c
)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Raylib statically
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Windows-specific configurations for standalone .exe
if(WIN32)
    # Add necessary libraries for Windows
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)

    # Set compiler flags for static runtime 
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    
    # Add icon resource file for the executable
    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/resources.rc)
    
    # Remove console window (GUI application)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# For Linux static linking
if(UNIX AND NOT APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE -static-libstdc++ -static-libgcc)
endif()

# For macOS bundle 
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Pacman"
    )
endif()

# Debugging and status messages
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Raylib: Found at ${raylib_DIR}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")