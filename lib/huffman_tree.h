//
// Created by daniil on 30.05.19.
//

#ifndef HUFFMAN_HUFFMAN_TREE_H
#define HUFFMAN_HUFFMAN_TREE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

struct huffman_tree {
    explicit huffman_tree(std::unordered_map<char, uint32_t> const &data);

    std::unordered_map<char, std::vector<bool>> const &get_keys() const;

    std::vector<char> const &get_tree();

    std::vector<char> const &get_keys_in_order() const;


private:

    void dfs(std::vector<bool> &seq_bits);

    struct qux {
        bool operator()(std::pair<uint32_t, std::string> const &a, std::pair<uint32_t, std::string> const &b);
    };

    std::unordered_map<char, std::vector<bool>> key_value;
    std::unordered_map<std::vector<bool>, char> value_key;
    std::vector<char> order_keys;
    std::vector<char> tree;
};

#endif //HUFFMAN_HUFFMAN_TREE_H
