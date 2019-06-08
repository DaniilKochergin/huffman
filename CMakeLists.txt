cmake_minimum_required(VERSION 3.14)
project(huffman)

include_directories(${HUFFMAN_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman huffman_testing.cpp
        utilita/buffered_reader.cpp
        lib/huffman_tree.cpp
        utilita/buffered_writer.cpp
        utilita/file_compressor.cpp
        utilita/file_decompressor.cpp
        lib/decompressor.cpp
        lib/compressor.cpp
        lib/data_source.cpp
        lib/huffman_tree.h
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc
        )
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif ()

target_link_libraries(huffman -lpthread)
