//
// Created by Iman Gholami on 4/5/24.
//

#ifndef CMSC701_A1_BINARY_READER_H
#define CMSC701_A1_BINARY_READER_H

#include <string>
#include <vector>

namespace bitvector {
    class binary_reader {

    public:
        binary_reader(std::string filename);

        std::vector<unsigned long long > data;
        int size;
    };
}

#endif //CMSC701_A1_BINARY_READER_H
