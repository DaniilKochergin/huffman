//
// Created by daniil on 30.05.19.
//
#include <queue>
#include <string>
#include <algorithm>
#include "huffman_tree.h"

huffman_tree::huffman_tree(std::unordered_map<char, uint32_t> const &data) {
    std::priority_queue<std::pair<uint32_t, std::string>, std::vector<std::pair<uint32_t, std::string>>, qux> q;
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::string s;
        s.push_back(it->first);
        q.push(std::make_pair(it->second, s));
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
        std::reverse(key.second.begin(), key.second.end());
        value_key[key.second] = key.first;
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
        res.push_back('U');
        order_keys.push_back(value_key.begin()->second);
        return res;
    }
    if (value_key.empty()) {
        res.push_back('U');
        return res;
    }
    std::vector<bool> seq_bits;
    dfs(res, seq_bits);
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
