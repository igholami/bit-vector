//
// Created by Iman Gholami on 4/9/24.
//

#include <boost/program_options.hpp>
#include <iostream>
#include "binary_reader.h"
#include "compact_vector.h"
#include "bitvector.h"
#include <fstream>
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "query_reader.h"

namespace po = boost::program_options;
namespace bv = bitvector;

class input_parser {

public:
    void parse(int argc, char* argv[]) {
        po::options_description desc;
        desc.add_options()
                ("index", po::value<std::string>(&this->index)->required(), "The path to the bitvector with rank index that was computed by rsbuild as described above")
                ("query_file", po::value<std::string>(&this->query_file)->required(), "A text-format query file (structure defined below) that consists of a set of rank queries")
                ("output_path", po::value<std::string>(&this->output_path)->required(), "The path to a file where you should write (in text) the output of the queries")
                ;
        po::positional_options_description pd;
        pd.add("index", 1);
        pd.add("query_file", 1);
        pd.add("output_path", 1);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pd).run(), vm);
        po::notify(vm);
    }

    std::string index;
    std::string output_path;
    std::string query_file;
};

int main(int argc, char* argv[]) {
    input_parser inputParser;
    inputParser.parse(argc, argv);

    bv::bitvector rank;
    {
        std::ifstream file(inputParser.index);
        cereal::BinaryInputArchive archive(file);
        archive(rank);
    }

    std::ofstream out(inputParser.output_path);
    bv::query_reader queryReader(inputParser.query_file);
    for(int query: queryReader.get_queries()) {
        out << query << ":" << rank.select(query) << std::endl;
    }
    out.close();

    return 0;
}