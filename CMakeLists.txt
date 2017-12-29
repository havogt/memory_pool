project(memory_pool CXX)
cmake_minimum_required(VERSION 3.5)

add_executable( main src/main.cc )

add_subdirectory( test )

