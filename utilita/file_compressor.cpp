//
// Created by daniil on 30.05.19.
//

#include <string>
#include <iostream>
#include "file_compressor.h"
#include "buffered_reader.h"
#include "buffered_writer.h"
#include "../lib/compressor.h"
#include "../lib/data_source.h"
#include "../lib/huffman_tree.h"

void compress(std::string const &input, std::string const &output) {
    buffered_reader reader(input);
    buffered_writer writer(output);
    data_source data;
    while (!reader.eof()) {
        data.put(reader.read());
    }
    compressor compressor(data);
    std::vector<char> tmp(compressor.get_size());
    for (char cur:tmp) {
        writer.write(cur);
    }
    tmp = compressor.get_huffman_code();
    for (char cur : tmp) {
        writer.write(cur);
    }
    tmp = compressor.get_compressed_code(data.get_data());
    for (char cur : tmp) {
        writer.write(cur);
    }
}

void block_compress(std::string const &input, std::string const &output, size_t block_sz = 5) {
    buffered_reader reader1(input);
    buffered_writer writer(output);
    data_source data1;
    while (!reader1.eof()) {
        for (size_t i = 0; i < block_sz && !reader1.eof(); ++i) {
            data1.put(reader1.read());
        }
        data1.clear_data();
    }
    compressor compressor(data1);
    std::vector<char> tmp(compressor.get_size());
    for (char cur:tmp) {
        writer.write(cur);
    }
    tmp = compressor.get_huffman_code();
    for (char cur : tmp) {
        writer.write(cur);
    }
    buffered_reader reader(input);
    data_source data;
    while (!reader.eof()) {
        data.clear_data();
        for (size_t i = 0; i < block_sz && !reader.eof(); ++i) {
            data.put(reader.read());
        }
        tmp = compressor.get_compressed_code(data.get_data());
        for (char cur : tmp) {
            writer.write(cur);
        }
    }
}

