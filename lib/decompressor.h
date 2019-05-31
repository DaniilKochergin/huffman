//
// Created by daniil on 31.05.19.
//

#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include <vector>
#include <cstdint>

struct decompressor {
    decompressor(std::vector<std::pair<char, uint32_t>> _keys, std::vector<char> data);
    ~decompressor() = default;
    std::vector<char> decompress() const;
private:
    std::vector<std::pair<char, uint32_t>> keys;
    std::vector<char> data;
};


#endif //HUFFMAN_DECOMPRESSOR_H
