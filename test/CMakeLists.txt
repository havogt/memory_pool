include( ../cmake/googletest-download/googletest-download.cmake)

add_executable( test_example test_example.cc )
target_link_libraries( test_example gtest gtest_main )

add_executable( test_variant1 variant1/test_variant1.cc )
target_link_libraries( test_variant1 gtest gtest_main )

add_executable( test_variant2 variant2/test_variant2.cc )
target_link_libraries( test_variant2 gtest gtest_main )
