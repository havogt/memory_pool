include( ../cmake/googletest-download/googletest-download.cmake)

add_executable( test_example test_example.cc )
target_link_libraries( test_example gtest gtest_main )

add_executable( test_variant1 variant1/test_variant1.cc )
target_link_libraries( test_variant1 gtest gtest_main )

add_executable( test_variant2 variant2/test_variant2.cc )
target_link_libraries( test_variant2 gtest gtest_main )

add_executable( test_save_ctor save_ctor/test_save_ctor.cc )
target_link_libraries( test_save_ctor gtest gtest_main )

find_package(Boost 1.58 REQUIRED)

add_executable( test_multi_object_pool multi_object_pool/test_multi_object_pool.cc )
target_link_libraries( test_multi_object_pool gtest gtest_main )
target_include_directories( test_multi_object_pool PRIVATE ${Boost_INCLUDE_DIR} )
