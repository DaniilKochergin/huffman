#include <iostream>
#include "lib/huffman_tree.h"
#include <vector>
#include <iostream>
#include "utilita/buffered_reader.h"
#include "utilita/buffered_writer.h"
#include "utilita/file_compressor.h"
#include "utilita/file_decompressor.h"

using namespace std;

int main() {
    block_compress("/home/daniil/CLionProjects/huffman/input.txt", "/home/daniil/CLionProjects/huffman/out.txt", 1024);
    block_decompress("/home/daniil/CLionProjects/huffman/out.txt", "/home/daniil/CLionProjects/huffman/input.txt",
                     1024);
//    buffered_reader bf("/home/daniil/CLionProjects/huffman/input.txt");
//    buffered_writer bw("/home/daniil/CLionProjects/huffman/out.txt");
//    while (!bf.eof()) {
//        bw.wibf.read() << endl;
//    }
//    vector<uint32_t> v(256);
//    // v['a'] = 2;
//    huffman_tree tr(v);
//    vector<pair<char, vector<bool>>> res = tr.get_keys();
//    for (int i = 0; i < tr.get_keys().size(); ++i) {
//        cout << tr.get_keys()[i].first << " ";
//        for (int j = 0; j < tr.get_keys()[i].second.size(); ++j) {
//            cout << tr.get_keys()[i].second[j];
//        }
//        cout << endl;
//    }
//    vector<char> tt = tr.get_tree();
//    for (int i = 0; i < tt.size(); ++i) {
//        cout << tt[i] << " ";
//    }

    return 0;
}