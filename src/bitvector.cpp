//
// Created by Iman Gholami on 4/9/24.
//

#include <iostream>
#include <cmath>
#include "bitvector.h"

namespace bitvector {
    bitvector::bitvector(compact_vector vector) {
        this->vector = vector;
        super_block_word_size = find_covering_size(vector.size());
        block_size = ceil(0.5*log2(vector.size()));
        super_block_size = block_size * block_size * 4;
        block_word_size = find_covering_size(super_block_size);
        compact_vector super_block_data(super_block_word_size);
        compact_vector block_data(block_word_size);
        {
            int cumulative_rank = 0;
            for (int i = 0; i < vector.size(); i += super_block_size) {
//                std::cerr << "i: " << i << std::endl;
//                std::cerr << "cumulative_rank: " << cumulative_rank << std::endl;

                super_block_data.push_back(cumulative_rank);
//                std::cerr << "cumulative_rank: " << super_block_data.get(super_block_data.size()-1) << std::endl;
                for (int j = 0; j < super_block_size && j + i < vector.size(); j++)
                    cumulative_rank += vector.get(i + j);

                int inside_cumulative_rank = 0;
                for (int j = 0; j < super_block_size; j += block_size) {
                    block_data.push_back(inside_cumulative_rank);
                    for (int k = 0; k < block_size && k + j < super_block_size && k + j + i < vector.size(); k++)
                        inside_cumulative_rank += vector.get(i + j + k);
                }
            }
        }
        this->super_block = super_block_data;
        this->block = block_data;
    }

    int bitvector::find_covering_size(unsigned long long max_value) {
        return 64 - __builtin_clzll(max_value);
    }

    void bitvector::details() {
        std::cerr << "Vector: " << std::endl;
        vector.details();
        std::cerr << "Super Block: " << std::endl;
        super_block.details();
        std::cerr << "Block: " << std::endl;
        block.details();
    }

    int bitvector::rank(int index) {
        int super_block_index = index / super_block_size;
        int block_index = (index % super_block_size) / block_size;
        int total_block_index = super_block_index * (super_block_size / block_size) + block_index;
        int inside_block_index = index % super_block_size % block_size;
//        std::cerr << "super_block_index: " << super_block_index << std::endl;
//        std::cerr << "block_index: " << block_index << std::endl;
//        std::cerr << "total_block_index: " << total_block_index << std::endl;
//        std::cerr << "inside_block_index: " << inside_block_index << std::endl;

        int super_block_rank = super_block.get(super_block_index);
        int block_rank = block.get(total_block_index);
        int cumulative_rank = super_block_rank + block_rank;
//        std::cerr << "super_block_rank: " << super_block_rank << std::endl;
//        std::cerr << "block_rank: " << block_rank << std::endl;
//        std::cerr << "cumulative_rank: " << cumulative_rank << std::endl;
        int start_index = super_block_index * super_block_size + block_index * block_size;
        int range = vector.get_range(start_index, start_index + inside_block_index);
        cumulative_rank += __builtin_popcountll(range);
//        for (int i = 0; i < inside_block_index; i++)
//            cumulative_rank += vector.get(super_block_index * super_block_size + block_index * block_size + i);
//        std::cerr << "cumulative_rank 2: " << cumulative_rank << std::endl;
//        std::cerr << "----------------" << std::endl;
        return cumulative_rank;
    }

    int bitvector::select(int rank) {
        int l = -1, r = vector.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (this->rank(m) <= rank)
                l = m;
            else
                r = m;
        }
        return this->rank(l) == rank ? l : -1;
    }
} // bitvector