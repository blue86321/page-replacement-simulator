cmake_minimum_required(VERSION 3.24)
project(page_replace_simulator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(page_replace_simulator main.cpp ${SOURCES})

target_include_directories(page_replace_simulator
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# testing binary
add_executable(simulator_test test.cpp ${SOURCES})
#target_link_libraries(test PRIVATE sum_integers)
target_include_directories(simulator_test
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# enable testing functionality
enable_testing()

# define tests
add_test(
    NAME page_replace_simulator_test
    COMMAND $<TARGET_FILE:simulator_test>
)