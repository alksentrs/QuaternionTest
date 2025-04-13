cmake_minimum_required(VERSION 3.10)
project(QuaternionTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find OpenMP
find_package(OpenMP REQUIRED)

# Include source directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    src/business
    src/business/engine
    src/application
    src/util
    src/quickhull
)

# Collect all sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/business/*.cpp
    src/util/*.cpp
    src/presentation/*.cpp
)

# Define the executable
add_executable(${PROJECT_NAME}
    src/application/main.cpp
    ${SOURCES}
)

# Link everything using modern style (PRIVATE)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        OpenGL::GL
        OpenGL::GLU
)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

# Optional: silence CMP0072 warning (OpenGL GLVND)
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()
