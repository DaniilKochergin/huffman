//
// Created by daniil on 31.05.19.
//

#include "compressor.h"


compressor::compressor(data_source const &data) : tree(data.get_count_data()) {}

std::vector<char> compressor::get_huffman_code() {
    std::vector<char> const huff_tree = tree.get_tree();
    std::vector<bool> binary_code_tree;
    for (size_t i = 0; i < huff_tree.size(); ++i) {
        if (huff_tree[i] == 'L') {
            binary_code_tree.push_back(true);
            binary_code_tree.push_back(false);
        }

        if (huff_tree[i] == 'R') {
            binary_code_tree.push_back(false);
            binary_code_tree.push_back(true);
        }

        if (huff_tree[i] == 'U') {
            binary_code_tree.push_back(false);
            binary_code_tree.push_back(false);
        }
    }
    std::vector<char> res(transpose(binary_code_tree));
    std::vector<char> tmp(tree.get_keys_in_order());
    for (size_t i = 0; i < tmp.size(); ++i) {
        res.push_back(tmp[i]);
    }
    return res;
}

std::vector<char> compressor::get_compressed_code(std::vector<char> const &data) {

    uint32_t sz = data.size();
    std::vector<bool> tmp;
    for(size_t i =0;i<32;++i){
        tmp.push_back((sz>>(31-i))&1);
    }
    size = transpose(tmp);
    std::unordered_map<char, std::vector<bool>> const keys = tree.get_keys();
    tmp.clear();
    for (size_t i = 0; i < data.size(); ++i) {
        auto it = keys.find(data[i]);
        for (size_t j = 0; j < it->second.size(); ++j) {
            tmp.push_back(it->second[i]);
        }
    }
    return transpose(tmp);
}

std::vector<char> compressor::transpose(std::vector<bool> v) const {
    std::vector<char> res;
    for (char i = 0; i <= v.size() / 8; ++i) {
        if (i*8<v.size()) res.push_back(0);
        for (char j = 0; j < 8; ++j) {
            if (i*8+j>=v.size()) break;
            res[i] |= (static_cast<char>(v[i * 8 + j]) << (8 - j - 1));
        }
    }
    return res;
}

std::vector<char> const &compressor::get_size() const {
    return size;
}
