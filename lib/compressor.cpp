//
// Created by daniil on 31.05.19.
//

#include <algorithm>
#include "compressor.h"


compressor::compressor(data_source const &data) : tree(data.get_count_data()) {
    size_code = data.get_size();
    std::vector<bool> tmp;
    for (size_t i = 0; i < 32; ++i) {
        tmp.push_back((size_code >> (31 - i)) & 1);
    }
    transpose(tmp, size);
}

void compressor::get_huffman_code(std::vector<char> & res) {
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
    transpose(binary_code_tree, res);
    std::vector<char> tmp(tree.get_keys_in_order());
    for (size_t i = 0; i < tmp.size(); ++i) {
        res.push_back(tmp[i]);
    }
}

void compressor::get_compressed_code(std::vector<char> const &data, std::vector<char> & res) {
    std::vector<bool> tmp;
    std::unordered_map<char, std::vector<bool>> const keys = tree.get_keys();
    size_code -= data.size();
    for (size_t i = 0; i < last_bits.size(); ++i) {
        tmp.push_back(last_bits[i]);
    }
    last_bits.clear();
    for (size_t i = 0; i < data.size(); ++i) {
        auto it = keys.find(data[i]);
        for (size_t j = 0; j < it->second.size(); ++j) {
            tmp.push_back(it->second[j]);
        }
    }
    if (size_code != 0) {
        while (tmp.size() % 8 != 0) {
            last_bits.push_back(tmp.back());
            tmp.pop_back();
        }
        std::reverse(last_bits.begin(), last_bits.end());
    }
    transpose(tmp, res);
}

void compressor::transpose(std::vector<bool> const &v, std::vector<char> &res) const {
    for (size_t i = 0; i * 8 < v.size(); ++i) {
        res.push_back(0);
        for (size_t j = 0; j < 8; ++j) {
            if (i * 8 + j >= v.size()) break;
            res[i] |= (static_cast<char>(v[i * 8 + j]) << (8 - j - 1));
        }
    }
}

std::vector<char> const &compressor::get_size() const {
    return size;
}
