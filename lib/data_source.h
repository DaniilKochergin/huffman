//
// Created by daniil on 31.05.19.
//

#ifndef HUFFMAN_DATA_SOURCE_H
#define HUFFMAN_DATA_SOURCE_H

#include <vector>
#include <unordered_map>

struct data_source {
    data_source() = default;

    ~data_source() = default;

    data_source(data_source const &other) = default;


    std::unordered_map<char, uint32_t> const &get_count_data() const;

    std::vector<char> const &get_data();


    uint32_t get_size() const;

    void put(char a);

    void clear_data();

private:
    uint32_t size = 0;
    std::unordered_map<char, uint32_t> count_data;
    std::vector<char> data;
};


#endif //HUFFMAN_DATA_SOURCE_H
