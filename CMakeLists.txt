cmake_minimum_required (VERSION 2.6)
project (TrafficSim)
include_directories("src")

set(CMAKE_CXX_STANDARD 11)

# Set the name of the executable to be produced
set(EXECUTABLE_NAME TrafficSim)

file(GLOB_RECURSE LIBSRC src/*.cpp)

# Add all .cpp - files under src/ directory
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

find_package(SFML REQUIRED graphics window audio system)
target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio)

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic -g)