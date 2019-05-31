//
// Created by daniil on 30.05.19.
//
#include <queue>
#include <string>
#include <algorithm>
#include "huffman_tree.h"

huffman_tree::huffman_tree(std::vector<uint32_t> const &data) {
    std::priority_queue<std::pair<uint32_t, std::string>, std::vector<std::pair<uint32_t, std::string>>, qux> q;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] != 0) {
            std::string s;
            s.push_back(i);
            q.push(std::make_pair(data[i], s));
        }
    }
    if (q.size() == 1) {
        key_value[q.top().second[0]].push_back(false);
    }
    while (q.size() > 1) {
        std::string s1 = q.top().second;
        uint32_t size1 = q.top().first;
        q.pop();
        std::string s2 = q.top().second;
        uint32_t size2 = q.top().first;
        q.pop();
        for (char i : s1) {
            key_value[i].push_back(false);
        }
        for (char i : s2) {
            key_value[i].push_back(true);
        }
        s1 += s2;
        size1 += size2;
        q.push(make_pair(size1, s1));
    };

    for (auto &key : key_value) {
        std::vector<bool> tmp(key.second);
        std::reverse(tmp.begin(), tmp.end());
        value_key[tmp] = key.first;
    }

}

std::unordered_map<char, std::vector<bool>> const &huffman_tree::get_keys() const {
    return key_value;
}

std::vector<char> huffman_tree::get_tree() {
    std::vector<char> res;
    if (value_key.size() == 1) {
        res.push_back('L');
        res.push_back('U');
        return res;
    }
    if (value_key.empty()) {
        return res;
    }
    std::vector<bool> seq_bits;
    dfs(res, seq_bits);
    res.pop_back();
    return res;
}

void huffman_tree::dfs(std::vector<char> &v, std::vector<bool> &seq_bits) {
    auto it = value_key.find(seq_bits);
    if (it != value_key.end()) {
        v.push_back('U');
        order_keys.push_back(it->second);
        return;
    }
    v.push_back('L');
    seq_bits.push_back(false);
    dfs(v, seq_bits);
    seq_bits.pop_back();
    v.push_back('R');
    seq_bits.push_back(true);
    dfs(v, seq_bits);
    seq_bits.pop_back();
    v.push_back('U');
}

std::vector<char> const &huffman_tree::get_keys_in_order() const {
    return order_keys;
}

bool
huffman_tree::qux::operator()(std::pair<uint32_t, std::string> const &a, std::pair<uint32_t, std::string> const &b) {
    return a.first > b.first;
}
