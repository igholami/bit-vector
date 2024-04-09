//
// Created by Iman Gholami on 4/6/24.
//

#ifndef CMSC701_A1_COMPACT_VECTOR_H
#define CMSC701_A1_COMPACT_VECTOR_H

#include <vector>
#include <cstdint>
#include "cereal/access.hpp"

namespace bitvector {

    class compact_vector {
        std::vector<unsigned long long> data;
        unsigned long vector_size;
        char word_size;
    public:
        compact_vector() = default;
        compact_vector(std::vector<unsigned long long> data, unsigned char word_size);

        unsigned long long get(unsigned long long index) const;
        void set(unsigned long long index, unsigned long long value);
        unsigned long long size() const;
        void push_back(unsigned long long value);

        void details();

        compact_vector(int word_size);

        template<class Archive>
        void serialize(Archive& archive) {
            archive(this->data, this->vector_size, this->word_size);
        }

        void resize(unsigned long long size);

        unsigned long long get_range(unsigned long long start, unsigned long long end) const;
    };

} // bitvector

#endif //CMSC701_A1_COMPACT_VECTOR_H
