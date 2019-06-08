//
// Created by daniil on 30.05.19.
//

#include "buffered_writer.h"

buffered_writer::~buffered_writer() {
    if (begin > 0) writer.write(buffer, begin);
    writer.close();
}

buffered_writer::buffered_writer(std::string const &file) : writer(file, std::ofstream::binary), begin(0){
    if (writer.fail()){
        writer.close();
        throw std::runtime_error("Writer failed!");
    }

}

void buffered_writer::write(char a) {
    if (begin != BUFF_SIZE){
        buffer[begin++] = a;
    } else {
        writer.write(buffer, BUFF_SIZE);
        begin = 0;
        buffer[begin++]=a;
    }
}
