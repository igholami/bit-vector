//
// Created by Iman Gholami on 4/9/24.
//

#ifndef CMSC701_A1_QUERY_READER_H
#define CMSC701_A1_QUERY_READER_H

namespace bitvector {

    class query_reader {
        std::vector<int> queries;
    public:
        query_reader(std::string filname);

        std::vector<int> get_queries();
    };

} // bitvector

#endif //CMSC701_A1_QUERY_READER_H
