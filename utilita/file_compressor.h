//
// Created by daniil on 30.05.19.
//

#ifndef HUFFMAN_FILECOMPRESSOR_H
#define HUFFMAN_FILECOMPRESSOR_H

#include <string>

void compress(std::string const &input, std::string const &output);

void block_compress(std::string const &input, std::string const &output, size_t block_sz);

#endif //HUFFMAN_FILECOMPRESSOR_H
