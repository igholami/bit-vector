//
// Created by Iman Gholami on 4/9/24.
//

#ifndef CMSC701_A1_BITVECTOR_H
#define CMSC701_A1_BITVECTOR_H

#include "compact_vector.h"

namespace bitvector {

    class bitvector {
        compact_vector vector;
        compact_vector super_block;
        compact_vector block;

        int find_covering_size(unsigned long long max_value);

        int super_block_word_size;
        int block_size;
        int super_block_size;
        int block_word_size;

    public:
        bitvector(compact_vector vector);
        bitvector() = default;
        void details();

        template<class Archive>
        void serialize(Archive& archive) {
            archive(this->vector, this->super_block, this->block, this->super_block_word_size, this->block_size, this->super_block_size, this->block_word_size);
        }

        int rank(int index);
        int select(int rank);
    };

} // bitvector

#endif //CMSC701_A1_BITVECTOR_H
