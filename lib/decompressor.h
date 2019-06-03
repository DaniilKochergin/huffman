//
// Created by daniil on 31.05.19.
//

#ifndef HUFFMAN_DECOMPRESSOR_H
#define HUFFMAN_DECOMPRESSOR_H

#include <vector>
#include <cstdint>
#include <unordered_map>

struct decompressor {
    explicit decompressor(std::vector<char> const &a);

    ~decompressor() = default;

    std::vector<char> decompress();

    std::vector<char> decompress_block(std::vector<char> const &block);

    void check();

private:
    void dfs(std::vector<bool> &seq_bits, std::vector<std::vector<bool>> &keys);

    void parse_keys();

    std::vector<char> parse_data();

    static std::vector<bool> transpose(std::vector<char> const &v);

    struct tokenizer {
        explicit tokenizer(std::vector<char> const &v);

        bool get();

        char get_char();

        void align();

        void resize(std::vector<char> const &v);

        bool eof();

        void back(size_t size_);

    private:
        std::vector<bool> binary_data;
        size_t index;
    };

    std::vector<bool> last_bits;
    uint32_t size;
    std::unordered_map<std::vector<bool>, char> key_value;
    tokenizer data;
};


#endif //HUFFMAN_DECOMPRESSOR_H
