
cmake_minimum_required(VERSION 3.5)

# ---- binary ----

set(BENCH_NAME ${BINARY_NAME}-benchmarks)
add_executable(${BENCH_NAME} "")

target_link_libraries(${BENCH_NAME} PUBLIC ${BINARY_NAME})

# ---- cmake targets ----

add_custom_target(bench-${BENCH_NAME}
  COMMAND $<TARGET_FILE:${BENCH_NAME}>
  DEPENDS ${BENCH_NAME})

# ---- compiler targets ----

target_include_directories(${BENCH_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE BINARY_SOURCES
  "src/*.c" "src/*.cc" "src/*.cpp" "src/*.cxx")
target_sources(${BENCH_NAME} PRIVATE ${BINARY_SOURCES})

target_link_libraries(${BENCH_NAME} PRIVATE hayai_main)
