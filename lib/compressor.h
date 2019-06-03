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

    std::vector<char> get_compressed_code(std::vector<char> const &data);

    std::vector<char> const &get_size() const;

    uint32_t size_code;

private:

    std::vector<char> transpose(std::vector<bool> v) const;

    std::vector<bool> last_bits;
    huffman_tree tree;
    std::vector<char> size;
};


#endif //HUFFMAN_COMPRESSOR_H
