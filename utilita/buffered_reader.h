//
// Created by daniil on 30.05.19.
//

#ifndef HUFFMAN_BUFFERED_READER_H
#define HUFFMAN_BUFFERED_READER_H


#include <cstdio>
#include <fstream>
#include <string>

struct buffered_reader {
    buffered_reader() = delete;
    ~buffered_reader();
    explicit buffered_reader(std::string const & file);
    char read();
    bool eof();
private:
    const static size_t BUFF_SIZE = 1024;
    std::ifstream reader;
    char buffer[BUFF_SIZE];
    size_t begin;
    size_t end;
};


#endif //HUFFMAN_BUFFERED_READER_H
