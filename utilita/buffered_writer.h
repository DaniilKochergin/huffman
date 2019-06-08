//
// Created by daniil on 30.05.19.
//

#ifndef HUFFMAN_BUFFERED_WRITER_H
#define HUFFMAN_BUFFERED_WRITER_H


#include <cstdio>
#include <fstream>
struct buffered_writer {
    buffered_writer() = delete;
    ~buffered_writer();
    explicit buffered_writer(std::string const & file);
    void write(char a);
private:
    std::ofstream writer;
    size_t begin = 0;
    const static size_t BUFF_SIZE = 1024;
    char buffer[BUFF_SIZE];
};


#endif //HUFFMAN_BUFFERED_WRITER_H
