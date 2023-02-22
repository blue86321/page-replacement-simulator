cmake_minimum_required(VERSION 3.24)
project(page_replace_simulator)

set(CMAKE_CXX_STANDARD 20)

file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(example)

# testing
enable_testing()
add_subdirectory(tests)
