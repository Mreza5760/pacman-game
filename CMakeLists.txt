# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and language standard
project(Pacman C)
set(CMAKE_C_STANDARD 23)

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

# Include FetchContent for dependency management
include(FetchContent)

# Function to include a dependency from Git
function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(
        ${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

# Add Raylib dependency (static linking)
set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    message(STATUS "Fetching ${LIB1} from GitHub")
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.5)
else()
    message(STATUS "Using local ${LIB1}")
endif()

# Collect all .c files from the src directory
file(GLOB SOURCES src/*.c)

# Define the executable and link Raylib
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})

# Static linking for Windows
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
endif()

# Link Raylib statically and other necessary libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB1})

# Optional debug information
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Raylib: ${LIB1}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")