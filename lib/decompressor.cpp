//
// Created by daniil on 31.05.19.
//

#include <unordered_set>
#include "decompressor.h"

decompressor::decompressor(std::vector<char> const &a) : size(0), data(a) {}

void decompressor::decompress_block(std::vector<char> const &block, std::vector<char> & res) {
    data.resize(block);
    parse_data(res);
}

void decompressor::transpose(std::vector<char> const &v, std::vector<bool> & res) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < 8; ++j) {
            res.push_back((static_cast<char>(v[i]) >> (7 - j)) & 1);
        }
    }
}

void decompressor::decompress(std::vector<char> & res) {
    for (int i = 31; i >= 0; --i) {
        size |= (static_cast<uint32_t >(data.get()) << i);
    }
    parse_keys();
    parse_data(res);
}


void decompressor::parse_keys() {
    std::vector<bool> seq_bits;
    std::vector<std::vector<bool>> keys;
    if (size != 0) dfs(seq_bits, keys);
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

    dfs(seq_bits, keys);
    seq_bits.pop_back();

    f1 = data.get();
    f2 = data.get();

    if (!f1 && !f2) {
        return;
    } else {
        throw std::runtime_error("Bad huffman tree!");
    }
}

void decompressor::parse_data(std::vector<char> & res) {
    std::vector<bool> key;
    while (size > 0 && !data.eof()) {
        while (!data.eof()) {
            key.push_back(data.get());
            auto it = key_value.find(key);
            if (it != key_value.end()) {
                res.push_back(it->second);
                key.clear();
                size--;
                break;
            }
        }
    }
    data.back(key.size());
}


void decompressor::check() {
    if (size > 0) {
        throw std::runtime_error("Bad bits!");
    }
}

decompressor::tokenizer::tokenizer(std::vector<char> const &v) : index(0) {
    transpose(v, binary_data);
}

bool decompressor::tokenizer::get() {
    if (eof()) {
        throw std::runtime_error("Bad bits!");
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
    index += (8 - (index % 8));
}

void decompressor::tokenizer::resize(std::vector<char> const &v) {
    std::vector<bool> tmp;
    while (!eof()) {
        tmp.push_back(get());
    }
    binary_data.clear();
    for (size_t i = 0; i < tmp.size(); ++i) {
        binary_data.push_back(tmp[i]);
    }
    tmp.clear();
    transpose(v, tmp);
    for (size_t i = 0; i < tmp.size(); ++i) {
        binary_data.push_back(tmp[i]);
    }
    index = 0;
}

void decompressor::tokenizer::back(size_t size__) {
    index -= size__;
}


