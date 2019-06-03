//
// Created by daniil on 30.05.19.
//

#include "buffered_reader.h"

buffered_reader::buffered_reader(std::string const &file__) : reader(file__, std::ifstream::binary), begin(0), end(0) {
    if (reader.fail()) {
        reader.close();
        throw std::runtime_error("Bad file!");
    }
}

buffered_reader::~buffered_reader() {
    reader.close();
}


char buffered_reader::read() {
    if (begin != end) {
        return buffer[begin++];
    } else {
        if (reader.eof()) {
            throw std::runtime_error("Read from end of file!");
        }
        reader.read(buffer, BUFF_SIZE);
        begin = 0;
        end = reader.gcount();
        return buffer[begin++];
    }
}

bool buffered_reader::eof() {
    if (begin == end){
        reader.read(buffer, BUFF_SIZE);
        begin = 0;
        end = reader.gcount();
        return reader.eof() && end == 0;
    }
    return false;
}
