
cmake_minimum_required(VERSION 3.5)

# Define the output directory
set(PROJECT_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})

# Define project
project("project-initial" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD "20")
enable_testing()

add_subdirectory(project-lib)
add_subdirectory(project-bin)
