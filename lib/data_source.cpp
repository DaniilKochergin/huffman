//
// Created by daniil on 31.05.19.
//

#include <stdexcept>
#include "data_source.h"

data_source::data_source(size_t size) : count_data(size) {}

void data_source::put(char a) {
    if (static_cast<size_t>(a) >= count_data.size()) {
        throw std::runtime_error("Bad size of data!");
    }
    count_data[a]++;
    data.push_back(a);
}

std::vector<uint32_t> const &data_source::get_count_data() const {
    return count_data;
}

std::vector<char> const &data_source::get_data() {
    return data;
}
