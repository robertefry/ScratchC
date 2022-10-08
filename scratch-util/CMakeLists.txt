
cmake_minimum_required(VERSION 3.5)

# Define binary
set(BINARY_NAME "scratch-util")
add_library(${BINARY_NAME} INTERFACE)
add_subdirectory(tests)
add_subdirectory(benchmarks)

# Define include directories
target_include_directories(${BINARY_NAME} INTERFACE "include")

# Use threads
find_package(Threads)
target_link_libraries(${BINARY_NAME} INTERFACE ${CMAKE_THREAD_LIBS_INIT})

# Use fmt (header-only)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${BINARY_NAME} INTERFACE fmt::fmt-header-only)

# Use spdlog (header-only)
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${BINARY_NAME} INTERFACE spdlog::spdlog_header_only)
