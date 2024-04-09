//
// Created by Iman Gholami on 4/6/24.
//

#include <iostream>
#include "compact_vector.h"

namespace bitvector {
    unsigned long long compact_vector::get(unsigned long long index) const {
        if (index >= vector_size) {
            throw std::out_of_range("Index out of range");
        }
        unsigned long long first_index = index * word_size / 64;
        unsigned long long first_offset = index * word_size % 64;
        unsigned long long second_index = (index + 1) * word_size / 64;
        unsigned long long second_offset = (index + 1) * word_size % 64;
        unsigned long long mask = (1 << word_size) - 1;
        if (first_index == second_index){
            return (data[first_index] >> first_offset) & mask;
        }
        else {
            return ((data[first_index] >> first_offset & mask) |
                    (data[second_index] & (mask >> (64 - first_offset))) << (64 - first_offset));
        }
//        return ((data[first_index] >> first_offset& mask) | (data[second_index] & (mask >> (64 - second_offset))) << (64 - second_offset));
    }

    void compact_vector::set(unsigned long long int index, unsigned long long int value) {
        if (index >= vector_size) {
            throw std::out_of_range("Index out of range");
        }
        unsigned long long first_index = index * word_size / 64;
        unsigned long long first_offset = index * word_size % 64;
        unsigned long long second_index = (index + 1) * word_size / 64;
        unsigned long long second_offset = (index + 1) * word_size % 64;
        unsigned long long mask = (1 << word_size) - 1;
        data[first_index] = (data[first_index] & ~(mask << first_offset)) | ((value & mask) << first_offset);
        if (first_index != second_index)
            data[second_index] = (data[second_index] & ~(mask >> (64 - first_offset))) | ((value & mask) >> (64 - first_offset));
    }

    unsigned long long compact_vector::size() const {
        return vector_size;
    }

    void compact_vector::push_back(unsigned long long value) {
        unsigned long long int index = vector_size * word_size / 64;
        unsigned long long int offset = vector_size * word_size % 64;
        unsigned long long int mask = (1 << word_size) - 1;
        if (offset + word_size <= 64) {
            if (offset == 0)
                data.push_back(0);
            data[index] = (data[index] & ~(mask << offset)) | ((value & mask) << offset);
        } else {
            data[index] = (data[index] & ~(mask << offset)) | ((value & mask) << offset);
            data.push_back((value & mask) >> (64 - offset));
        }
        vector_size++;
    }

    compact_vector::compact_vector(std::vector<unsigned long long> data, unsigned char word_size) {
        this->word_size = word_size;
        for (auto value : data) {
            push_back(value);
        }
    }

    void compact_vector::details() {
        std::cerr << "word_size: " << (int)word_size << std::endl;
        std::cerr << "vector_size: " << vector_size << std::endl;
        std::cerr << "data_size: " << data.size() << std::endl;
    }

    compact_vector::compact_vector(int word_size) {
        this->word_size = word_size;
        this->vector_size = 0;
    }

    void compact_vector::resize(unsigned long long int size) {
        while (vector_size < size) {
            push_back(0);
        }
    }

    unsigned long long compact_vector::get_range(unsigned long long int start, unsigned long long int end) const {
        int bit_count = (end - start) * word_size;
        if (bit_count > 64) {
            throw std::out_of_range("Range too large");
        }
        unsigned long long int first_index = start * word_size / 64;
        unsigned long long int first_offset = start * word_size % 64;
        unsigned long long int second_index = end * word_size / 64;
        unsigned long long int second_offset = end * word_size % 64;
        unsigned long long int mask = (1 << bit_count) - 1;
        if (first_index == second_index) {
            return (data[first_index] >> first_offset) & mask;
        } else {
            return ((data[first_index] >> first_offset & mask) |
                    (data[second_index] & (mask >> (64 - first_offset))) << (64 - first_offset));
        }
    }
}