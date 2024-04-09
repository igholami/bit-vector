//
// Created by Iman Gholami on 4/9/24.
//

#include <vector>
#include <string>
#include <fstream>
#include "query_reader.h"

namespace bitvector {
    query_reader::query_reader(std::string filename) {
        this->queries = std::vector<int>();
        std::ifstream file(filename);
        while (not file.eof()) {
            std::string type;
            int query;
            file >> type;
            if (file.eof())
                break;
            file >> query;
            this->queries.push_back(query);
        }
    }

    std::vector<int> query_reader::get_queries() {
        return this->queries;
    }
} // bitvector