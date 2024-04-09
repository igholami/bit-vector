//
// Created by Iman Gholami on 4/5/24.
//
#include <boost/program_options.hpp>
#include <iostream>
#include "binary_reader.h"
#include "compact_vector.h"
#include "bitvector.h"
#include <fstream>
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"

namespace po = boost::program_options;
namespace bv = bitvector;

class input_parser {

public:
    void parse(int argc, char* argv[]) {
        po::options_description desc;
        desc.add_options()
                ("input_bitvector_file", po::value<std::string>(&this->input_bitvector_file)->required(), "path to a file containing the input bitvector in a binary format")
                ("output_path", po::value<std::string>(&this->output_path)->required(), "path to a file where you should write the binary representation of the bitvector and your rank index")
                ;
        po::positional_options_description pd;
        pd.add("input_bitvector_file", 1);
        pd.add("output_path", 1);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pd).run(), vm);
        po::notify(vm);
    }

    std::string input_bitvector_file;
    std::string output_path;
};

int main(int argc, char* argv[]) {
    input_parser inputParser;
    inputParser.parse(argc, argv);

    bv::binary_reader reader(inputParser.input_bitvector_file);
    bv::compact_vector cv(reader.data, 1);
    cv.details();

    bv::bitvector rank(cv);
    rank.details();

    std::ofstream file(inputParser.output_path);
    cereal::BinaryOutputArchive archive(file);
    archive(rank);
    file.close();
    return 0;
}