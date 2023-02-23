file(COPY ../input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB test_files "test_*.cpp")
foreach(file ${test_files})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
    add_executable(${file_without_ext} ${file})
    include_directories(../input)
    target_link_libraries(${file_without_ext} simulator_src)
    target_include_directories(${file_without_ext}
        PRIVATE
            ../include
    )
    add_test(${file_without_ext} ${file_without_ext})

    set_tests_properties(${file_without_ext}
        PROPERTIES
            PASS_REGULAR_EXPRESSION "Test passed")
    set_tests_properties(${file_without_ext}
        PROPERTIES
            FAIL_REGULAR_EXPRESSION "(Exception|Test failed)")
endforeach()


##set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
##set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
##
###file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
##
##
##
##file(GLOB files "test_*.cpp")
##
##foreach(file ${files})
##    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
##    add_executable(${file_without_ext} ${file} ${SOURCES})
##    target_link_libraries(${file_without_ext} ${PROJECT_LIBS})
###    target_include_directories(${file_without_ext}
###        PUBLIC
###            $<INSTALL_INTERFACE:include>
###            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
###    )
##    add_test(${file_without_ext} ${file_without_ext})
##    set_tests_properties(${file_without_ext}
##            PROPERTIES
##            PASS_REGULAR_EXPRESSION "Test passed")
##    set_tests_properties(${file_without_ext}
##            PROPERTIES
##            FAIL_REGULAR_EXPRESSION "(Exception|Test failed)")
##    set_tests_properties(${file_without_ext}
##            PROPERTIES
##            TIMEOUT 120)
##endforeach()
##file(GLOB_RECURSE SRCS ../src/*.cpp)
#
#file(GLOB test_files "test_*.cpp")
#foreach(file ${test_files})
#    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
#    add_executable(${file_without_ext} ${file})
##    include_directories(${CMAKE_SOURCE_DIR}/src)
##    target_link_directories(${file_without_ext} PUBLIC ${PROJECT_BINARY_DIR}/src)
#    target_include_directories(${file_without_ext}
#        PUBLIC
#            $<INSTALL_INTERFACE:../include>
#            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
#    )
#    add_test(${file_without_ext} ${file_without_ext})
#endforeach()