//
// Created by daniil on 31.05.19.
//

#include <stdexcept>
#include "data_source.h"

void data_source::put(char a) {
    size++;
    count_data[a]++;
    data.push_back(a);
}

std::unordered_map<char, uint32_t> const &data_source::get_count_data() const {
    return count_data;
}

std::vector<char> const &data_source::get_data() {
    return data;
}

void data_source::clear_data() {
    data.clear();
}

uint32_t data_source::get_size() const {
    return size;
}
