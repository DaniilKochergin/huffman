#include <iostream>
#include "lib/huffman_tree.h"
#include <vector>
#include <iostream>
#include <random>
#include "utilita/buffered_reader.h"
#include "utilita/buffered_writer.h"
#include "utilita/file_compressor.h"
#include "utilita/file_decompressor.h"
#include "gtest/gtest.h"


namespace {

    size_t number_of_iterations = 1;
    std::string const fn1("/home/daniil/CLionProjects/huffman/f1.txt");
    std::string const fn2("/home/daniil/CLionProjects/huffman/f2.txt");
    std::string const fn3("/home/daniil/CLionProjects/huffman/f3.txt");


    void something_changes(std::string const &filename) {
        std::string s;
        std::ifstream reader(filename, std::ifstream::binary);
        while (!reader.eof()) {
            char *tmp = new char[256];
            reader.read(tmp, 256);
            for (size_t i = 0; i < reader.gcount(); ++i) {
                s.push_back(tmp[i]);
            }
            delete[] tmp;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        auto dist = std::uniform_int_distribution(0, static_cast<int>(s.size()));
        reader.close();

        int ind = dist(gen);
        s[ind] = static_cast<char>(~static_cast<int>(s[ind]));
        char *out = new char[s.size()];

        for (size_t i = 0; i < s.size(); ++i) {
            out[i] = s[i];
        }
        std::ofstream writer(filename, std::ofstream::binary);

        writer.write(out, s.size());

    }


    void add_something(std::string const &filename) {
        std::string s;
        std::ifstream reader(filename, std::ifstream::binary);
        while (!reader.eof()) {
            char *tmp = new char[256];
            reader.read(tmp, 256);
            for (size_t i = 0; i < reader.gcount(); ++i) {
                s.push_back(tmp[i]);
            }
            delete[] tmp;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        auto dist = std::uniform_int_distribution(0, static_cast<int>(s.size()));
        reader.close();

        s.push_back(s.back());
        s.push_back(s[0]);
        s.push_back(s[0]);
        s.push_back(s.back());

        char *out = new char[s.size()];

        for (size_t i = 0; i < s.size(); ++i) {
            out[i] = s[i];
        }
        std::ofstream writer(filename, std::ofstream::binary);

        writer.write(out, s.size());

    }

    bool equals_files(std::string const &filename1, std::string const &filename2) {
        std::ifstream file1(filename1, std::ifstream::binary);
        std::ifstream file2(filename2, std::ifstream::binary);
        if (file1.fail() || file2.fail()) {
            file1.close();
            file2.close();
            return false;
        }

        while (!file1.eof() && !file2.eof()) {
            if (file1.get() != file2.get()) {
                file1.close();
                file2.close();
                return false;
            }
        }
        if (!file1.eof() || !file2.eof()) {
            file1.close();
            file2.close();
            return false;
        }
        file1.close();
        file2.close();
        return true;
    }

    void generate_file(std::string const &filename, size_t size) {
        std::ofstream writer(filename, std::ios::binary);
        char *s = new char[size];
        std::random_device rd;
        std::mt19937 gen(rd());
        auto dist = std::uniform_int_distribution(0, 255);
        for (size_t i = 0; i < size; ++i) {
            s[i] = dist(gen);
        }
        writer.write(s, size);
        writer.close();
    }
}


//TEST(corectness, testing_my_test) {
//    compress(fn1, fn2);
//    decompress(fn2, fn3);
//    EXPECT_TRUE(equals_files(fn1, fn3));
//    std::string p1("/home/daniil/CLionProjects/huffman/p1.png");
//    std::string p2("/home/daniil/CLionProjects/huffman/p2.png");
//    compress(p1, fn2);
//    decompress(fn2, p2);
//    EXPECT_TRUE(equals_files(p1, p2));
//}

TEST(corectness, testing_empty_file) {
    generate_file(fn1, 0);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, testing_one_byte_file) {
    generate_file(fn1, 1);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, testing_three_byte_file) {
    generate_file(fn1, 3);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, testing_compress_decompress_1kb) {
    generate_file(fn1, 1024);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, testing_compress_decompress_10kb) {
    generate_file(fn1, 10240);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, testing_compress_decompress_100kb) {
    generate_file(fn1, 102400);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}


TEST(corectness, testing_compress_decompress_1000kb) {
    generate_file(fn1, 1024000);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, testing_compress_decompress_10000kb) {
    generate_file(fn1, 10240000);
    compress(fn1, fn2);
    decompress(fn2, fn3);
    EXPECT_TRUE(equals_files(fn1, fn3));
}


TEST(corectness, block_testing_compress_decompress_1kb) {
    generate_file(fn1, 1024);
    block_compress(fn1, fn2, 1024);
    block_decompress(fn2, fn3, 1024);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, block_testing_compress_decompress_10kb) {
    generate_file(fn1, 10240);
    block_compress(fn1, fn2, 1024);
    block_decompress(fn2, fn3, 1024);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, block_testing_compress_decompress_100kb) {
    generate_file(fn1, 102400);
    block_compress(fn1, fn2, 1024);
    block_decompress(fn2, fn3, 1024);
    EXPECT_TRUE(equals_files(fn1, fn3));
}


TEST(corectness, block_testing_compress_decompress_1000kb) {
    generate_file(fn1, 1024000);
    block_compress(fn1, fn2, 1024);
    block_decompress(fn2, fn3, 1024);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, block_testing_compress_decompress_10000kb) {
    generate_file(fn1, 10240000);
    block_compress(fn1, fn2, 1024);
    block_decompress(fn2, fn3, 1024);
    EXPECT_TRUE(equals_files(fn1, fn3));
}

TEST(corectness, block_testing_any_size_compress_decompress_100kb) {
    for (size_t i = 0; i < 100; ++i) {
        generate_file(fn1, 102400);
        std::random_device rd;
        std::mt19937 gen(rd());
        auto dist = std::uniform_int_distribution(1024, 1024000);
        size_t block_size1 = dist(gen);
        size_t block_size2 = dist(gen);
        block_compress(fn1, fn2, block_size1);
        block_decompress(fn2, fn3, block_size2);
        EXPECT_TRUE(equals_files(fn1, fn3));
    }
}

TEST(corectness, block_testing_compress_decompress_random_size) {
    for (size_t i = 0; i < 100; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        auto dist = std::uniform_int_distribution(0, 10240000);
        block_compress(fn1, fn2, 1024);
        block_decompress(fn2, fn3, 1024);
        EXPECT_TRUE(equals_files(fn1, fn3));
    }
}


TEST(invalid_test, wrong_file_name) {
    EXPECT_ANY_THROW(compress("afsfsd.sdfdsa", fn1));
    EXPECT_ANY_THROW(block_compress("afsfsd.txt", fn1, 1024));
    EXPECT_ANY_THROW(decompress("afsfsd.sdfdsa", fn1));
    EXPECT_ANY_THROW(block_decompress("afsfsd.sdfdsa", fn1, 1024));
}

TEST(invalid_test, bad_bits_in_compressed_file) {
    generate_file(fn1, 102400);
    compress(fn1, fn2);
    try {
        decompress(fn1, fn3);
    } catch (...) {

    }
    for (size_t i = 0; i < number_of_iterations; ++i) {
        something_changes(fn2);
        try {
            decompress(fn2, fn3);
        } catch (...) {
            compress(fn1, fn2);
        }
        try {
            block_decompress(fn2, fn3, 1024);
        } catch (...) {
            compress(fn1, fn2);
        }
    }
}

TEST(invalid_test, extra_bits_in_compressed_file) {
    generate_file(fn1, 100);
    compress(fn1, fn2);
    add_something(fn2);
    try {
        decompress(fn2, fn3);
    } catch (...) {

    }
    try {
        block_decompress(fn2, fn3, 1024);
    } catch (...) {

    }
}

TEST(invalid_test, small_block_size) {
    generate_file(fn1, 102400);
    compress(fn1, fn2);
    EXPECT_ANY_THROW(block_decompress(fn2, fn3, 10));
    EXPECT_ANY_THROW(block_decompress(fn2, fn3, 0));
    EXPECT_ANY_THROW(block_decompress(fn2, fn3, 666));
    EXPECT_ANY_THROW(block_decompress(fn2, fn3, 1023));
    EXPECT_ANY_THROW(block_decompress(fn2, fn3, 1));
}
