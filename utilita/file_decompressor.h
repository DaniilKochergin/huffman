//
// Created by daniil on 30.05.19.
//

#ifndef HUFFMAN_FILEDECOMPRESSOR_H
#define HUFFMAN_FILEDECOMPRESSOR_H

#include <string>

void decompress(std::string const &input, std::string const &output);

void block_decompress(std::string const &input, std::string const &output, size_t block_sz);

#endif //HUFFMAN_FILEDECOMPRESSOR_H
