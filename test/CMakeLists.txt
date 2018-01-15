include( ../cmake/googletest-download/googletest-download.cmake)

add_executable( test_example test_example.cc )
target_link_libraries( test_example gtest gtest_main )

add_subdirectory(variant1)
