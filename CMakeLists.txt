
cmake_minimum_required(VERSION 3.0)

# Define project
project("ScratchC" LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD "20")

# Define the output directory
set(PROJECT_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIRECTORY})

# Define build target
file(GLOB_RECURSE SOURCES
    "src/*.c" "src/*.cc" "src/*.cpp" "src/*.cxx"
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PRIVATE "src")

# Define compiler configuration
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Weffc++ -pedantic)

# Use threads
find_package(Threads)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_custom_target(run
    COMMAND ${PROJECT_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
