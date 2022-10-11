
cmake_minimum_required(VERSION 3.5)
execute_process(COMMAND ${CMAKE_SOURCE_DIR}/bootstrap.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Use vcpkg toolchain file
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ".vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Define CMake directories
set(PROJECT_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})

# Define project
project("scratch-cpp" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD "20")
enable_testing()

add_subdirectory(scratch)
add_subdirectory(scratch-util)
