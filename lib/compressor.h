//
// Created by daniil on 31.05.19.
//

#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <vector>
#include <cstdint>
#include "data_source.h"
#include "huffman_tree.h"

struct compressor {
    explicit compressor(data_source const &data);

    std::vector<char> get_huffman_code();

    std::vector<char> get_compressed_code(std::vector<char> const &data) const;

private:

    std::vector<char> transpose(std::vector<bool> v) const;
    huffman_tree tree;
};


#endif //HUFFMAN_COMPRESSOR_H
