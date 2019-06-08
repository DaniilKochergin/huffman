//
// Created by daniil on 08.06.19.
//

#include <iostream>
#include <cstring>
#include "utilita/file_compressor.h"
#include "utilita/file_decompressor.h"
#include <string>

int main(int count, char **args) {
    std::string f1 = args[2];
    std::string f2 = args[3];

    if (count == 4) {
        if (strcmp(args[1], "-c") == 0) {
            compress(f1, f2);
        } else if (strcmp(args[1], "-d") == 0) {
            decompress(f1, f2);
        }
    } else if (count == 5) {
        unsigned block_size = std::stoul(args[4]);
        if (strcmp(args[1], "-c") == 0) {
            block_compress(f1, f2, block_size);
        } else if (strcmp(args[1], "-d") == 0) {
            block_decompress(f1, f2, block_size);
        }
    } else {
        throw std::runtime_error("Wrong number of args!");
    }
    return 0;
}