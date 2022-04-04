
cmake_minimum_required(VERSION 3.5)

# Define binary
set(BINARY_NAME "project-lib")
add_library(${BINARY_NAME} SHARED "")

# Define compiler configuration
target_compile_options(${BINARY_NAME} PRIVATE -Wall -Wextra -Weffc++ -Wpedantic)
target_compile_options(${BINARY_NAME} PRIVATE -Wno-unused)

# Define include directories
target_include_directories(${BINARY_NAME} PUBLIC "include")
target_include_directories(${BINARY_NAME} PRIVATE "src")

# Define build sources
file(GLOB_RECURSE BINARY_SOURCES
  "src/*.c" "src/*.cc" "src/*.cpp" "src/*.cxx"
)
target_sources(${BINARY_NAME} PRIVATE ${BINARY_SOURCES})
