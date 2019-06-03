//
// Created by daniil on 30.05.19.
//

#include "file_decompressor.h"
#include "buffered_reader.h"
#include "buffered_writer.h"
#include "../lib/data_source.h"
#include "../lib/decompressor.h"

void decompress(const std::string &input, const std::string &output) {
    buffered_reader reader(input);
    buffered_writer writer(output);
    data_source data;
    while (!reader.eof()) {
        data.put(reader.read());
    }
    decompressor decompressor(data.get_data());
    std::vector<char> res;
    decompressor.decompress(res);
    for (size_t i = 0; i < res.size(); ++i) {
        writer.write(res[i]);
    }
    decompressor.check();
}

//block_sz must be >= huffman_tree + values size
void block_decompress(std::string const &input, std::string const &output, size_t block_sz = 1024) {
    if (block_sz < 1024) {
        throw std::runtime_error("Block size is small!");
    }
    buffered_reader reader(input);
    buffered_writer writer(output);
    data_source data;
    for (size_t i = 0; i < block_sz && !reader.eof(); ++i) {
        data.put(reader.read());
    }
    decompressor decompressor(data.get_data());
    std::vector<char> res;
    decompressor.decompress(res);
    for (size_t i = 0; i < res.size(); ++i) {
        writer.write(res[i]);
    }
    while (!reader.eof()) {
        data.clear_data();
        for (size_t i = 0; i < block_sz && !reader.eof(); ++i) {
            data.put(reader.read());
        }
        std::vector<char> tmp;
        decompressor.decompress_block(data.get_data(), tmp);
        for (size_t i = 0; i < tmp.size(); ++i) {
            writer.write(tmp[i]);
        }
    }
    decompressor.check();
}

