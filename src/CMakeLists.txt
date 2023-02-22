file(GLOB_RECURSE SOURCES *.cpp)

add_library(simulator_src ${SOURCES})
target_include_directories(simulator_src
    PUBLIC
        ../include
)
