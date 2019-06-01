//
// Created by daniil on 31.05.19.
//

#include <unordered_set>
#include "decompressor.h"

decompressor::decompressor(std::vector<char> const &a) : data(a), size(0) {}

std::vector<bool> decompressor::transpose(std::vector<char> const &v) {
    std::vector<bool> res;
    for (size_t i = 0; i <= v.size() / 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            if (i * 8 + j < v.size()) break;
            res.push_back((v[i] >> (8 - j)) & 1);
        }
    }
    return res;
}

std::vector<char> decompressor::decompress() {
    for (int i = 31; i >= 0; --i) {
        size |= (static_cast<uint32_t >(data.get()) << i);
    }
    parse_keys();
    std::vector<char> res;
    for (int i = 0; i < size; ++i) {
        std::vector<bool> key;
        while (true) {
            auto it = key_value.find(key);
            if (it != key_value.end()) {
                res.push_back(it->second);
                break;
            }
            key.push_back(data.get());
        }
    }
    data.align();
    if (!data.eof()){
        throw std::runtime_error("Extra bits in compressed file!");
    }
    return res;
}

void decompressor::parse_keys() {
    std::vector<bool> seq_bits;
    std::vector<std::vector<bool>> keys;
    dfs(seq_bits, keys);
    data.align();
    for (const auto &key : keys) {
        key_value[key] = data.get_char();
    }
}

void decompressor::dfs(std::vector<bool> &seq_bits, std::vector<std::vector<bool>> &keys) {
    bool f1 = data.get();
    bool f2 = data.get();
    if (f1 && !f2) {
        seq_bits.push_back(false);
    } else if (!f1 && f2) {
        seq_bits.push_back(true);
    } else if (!f1 && !f2) {
        keys.push_back(seq_bits);
        return;
    } else {
        throw std::runtime_error("Bad huffman tree!");
    }
    dfs(seq_bits, keys);

    seq_bits.pop_back();
    f1 = data.get();
    f2 = data.get();

    if (f1 && !f2) {
        seq_bits.push_back(false);
    } else if (!f1 && f2) {
        seq_bits.push_back(true);
    } else if (!f1 && !f2) {
        return;
    } else {
        throw std::runtime_error("Bad huffman tree!");
    }

    seq_bits.pop_back();

    f1 = data.get();
    f2 = data.get();

    if (!f1 && !f2) {
        return;
    } else {
        throw std::runtime_error("Bad huffman tree!");
    }
}

decompressor::tokenizer::tokenizer(std::vector<char> const &v) : binary_data(transpose(v)), index(0) {}

bool decompressor::tokenizer::get() {
    if (eof()) {
        throw std::runtime_error("Bad huffman tree!");
    }
    return binary_data[index++];
}

bool decompressor::tokenizer::eof() {
    return index >= binary_data.size();
}

char decompressor::tokenizer::get_char() {
    char a = 0;
    for (int i = 0; i < 8; ++i) {
        a |= (static_cast<char>(get()) << (7 - i));
    }
    return a;
}

void decompressor::tokenizer::align() {
    index += index % 8;
}

