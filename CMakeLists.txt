cmake_minimum_required(VERSION 3.14)
project(huffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(huffman main.cpp
        utilita/buffered_reader.cpp
        lib/huffman_tree.cpp
        utilita/buffered_writer.cpp
        utilita/file_compressor.cpp
        utilita/file_decompressor.cpp
        lib/decompressor.cpp
        lib/compressor.cpp
        lib/data_source.cpp
        lib/huffman_tree.h
        )
