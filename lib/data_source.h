//
// Created by daniil on 31.05.19.
//

#ifndef HUFFMAN_DATA_SOURCE_H
#define HUFFMAN_DATA_SOURCE_H

#include <vector>

struct data_source {
    data_source() = delete;
    ~data_source() = default;
    data_source(data_source const & other) = default;
    explicit data_source(size_t size);
    std::vector<uint32_t> const & get_count_data() const;
    std::vector<char> const & get_data();
    void put(char a);
private:
    std::vector<uint32_t> count_data;
    std::vector<char> data;
};


#endif //HUFFMAN_DATA_SOURCE_H
