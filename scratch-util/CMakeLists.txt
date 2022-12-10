
cmake_minimum_required(VERSION 3.12)

# ---- binary ----

set(BINARY_NAME "scratch-util")
add_library(${BINARY_NAME} INTERFACE)

# ---- compiler targets ----

target_include_directories(${BINARY_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${BINARY_NAME}
  INTERFACE
    fmt::fmt-header-only
    spdlog::spdlog_header_only
)

# ---- features ----

add_subdirectory(tests)
add_subdirectory(benchmarks)
