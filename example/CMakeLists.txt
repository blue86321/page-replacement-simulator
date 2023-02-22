#file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(example main.cpp)
target_link_libraries(example simulator_src)
target_include_directories(example
    PUBLIC
        ../include
        ../input
#        $<INSTALL_INTERFACE:../include>
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>

)