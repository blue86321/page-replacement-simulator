file(COPY ../input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_executable(example different_frames.cpp)
#target_link_libraries(example simulator_src)
#target_include_directories(example
#    PUBLIC
#        ../include
#)

file(GLOB files "*.cpp")
foreach(file ${files})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
    add_executable(${file_without_ext} ${file})
    target_link_libraries(${file_without_ext} simulator_src)
    target_include_directories(${file_without_ext}
        PRIVATE
            ../include
    )
endforeach()