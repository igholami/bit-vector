//
// Created by Iman Gholami on 4/5/24.
//

#include "binary_reader.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <bitset>



namespace bitvector {
    binary_reader::binary_reader(std::string filename) {
        // Read the file and populate the bitvector

        // return bitvector object filled by read a binary little endian file where first 4 byte is number of bits and next wi have a byte for each 8 bits
        std::vector<unsigned long long> data;
        int size = 0;

        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            file.read((char*)&size, sizeof(size));
            for (int i = 0; i < (size + 7) / 8; i++) {
                unsigned char byte;
                file.read((char*)&byte, sizeof(byte));
                for (int j = 0; j < 8 && i * 8 + j < size; j++) {
                    data.push_back((byte >> j) & 1);
                }
            }
        }

//        std::cout << "vector_size: " << size << std::endl;
//        for (auto byte : data) {
//            std::cout << byte;
//        }
//        std::cout << std::endl;

        this->data = data;
        this->size = size;
    }
}

