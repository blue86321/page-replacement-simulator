file(COPY ../input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(example main.cpp)
target_link_libraries(example simulator_src)
target_include_directories(example
    PUBLIC
        ../include
)