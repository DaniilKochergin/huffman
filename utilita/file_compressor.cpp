//
// Created by daniil on 30.05.19.
//

#include <string>
#include "file_compressor.h"
#include "buffered_reader.h"
#include "buffered_writer.h"
#include "../lib/compressor.h"
#include "../lib/data_source.h"
#include "../lib/huffman_tree.h"

void compress(std::string const &input, std::string const &output) {
    buffered_reader reader(input);
    buffered_writer writer(output);
    data_source data(256);
    while (!reader.eof()) {
        data.put(reader.read());
    }
    compressor compressor(data);
    compressor.get_compressed_code(data.get_data());
    std::vector<char> tmp(compressor.get_size());
    for(char cur:tmp){
        writer.write(cur);
    }
    tmp = compressor.get_huffman_code();
    for (char cur : tmp) {
        writer.write(cur);
    }
    tmp = compressor.get_compressed_code(data.get_data());
    for(char cur : tmp){
        writer.write(cur);
    }
}

