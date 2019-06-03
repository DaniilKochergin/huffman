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

    void get_huffman_code(std::vector<char> & res);

    void get_compressed_code(std::vector<char> const &data,  std::vector<char> & res);

    std::vector<char> const &get_size() const;

    uint32_t size_code;

private:

    void transpose(std::vector<bool> const &v, std::vector<char> & res) const;

    std::vector<bool> last_bits;
    huffman_tree tree;
    std::vector<char> size;
};


#endif //HUFFMAN_COMPRESSOR_H
