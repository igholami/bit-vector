//
// Created by Iman Gholami on 4/9/24.
//

#include <boost/program_options.hpp>
#include <iostream>
#include "binary_reader.h"
#include "compact_vector.h"
#include "bitvector.h"
#include <fstream>
#include <iomanip>
#include "command_reader.h"

namespace po = boost::program_options;
namespace bv = bitvector;

class input_parser {

public:
    void parse(int argc, char* argv[]) {
        po::options_description desc;
        desc.add_options()
                ("command_script", po::value<std::string>(&this->command_script)->required(), "A list of commands to populate and query the sparse array")
                ("output_path", po::value<std::string>(&this->output_path)->required(), "The path to an ouput location where the results of the commands above will be written")
                ;
        po::positional_options_description pd;
        pd.add("command_script", 1);
        pd.add("output_path", 1);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pd).run(), vm);
        po::notify(vm);
    }

    std::string command_script;
    std::string output_path;
};

int main(int argc, char* argv[]) {
    input_parser inputParser;
    inputParser.parse(argc, argv);



    std::ofstream out(inputParser.output_path);
    bv::command_reader commandReader(inputParser.command_script);
    bv::compact_vector v(1);
    std::vector<std::pair<int, std::string>> keys;
    bv::bitvector rank;
    for(auto command: commandReader.get_commands()) {
        if (command[0] == "init") {
            v.resize(std::stoi(command[1]));
        } else if (command[0] == "insert") {
            int index = std::stoi(command[1]);
            std::string value = command[2];
            v.set(index, 1);
            keys.push_back({index, value});
        } else if (command[0] == "finish") {
            sort(keys.begin(), keys.end());
            rank = bv::bitvector(v);
        } else if (command[0] == "query_index") {
            int index = std::stoi(command[1]);
            bool has_key = v.get(index);
            out << "idx:" << index << ":" << (has_key ? keys[rank.rank(index)].second : "-1") << "\n";
        } else if (command[0] == "query_rank") {
            int rank_query = std::stoi(command[1]);
            out << "qr:" << rank_query << ":" << (rank_query < keys.size() ? keys[rank_query].second : "-1") << "\n";
        } else if (command[0] == "rank_at_index") {
            int index = std::stoi(command[1]);
            out << "rai:" << index << ":" << rank.rank(index) << "\n";
        } else if (command[0] == "index_of_next_key") {
            int index = std::stoi(command[1]);
            int next_index = rank.select(rank.rank(index+1));
            out << "ink:" << index << ":" << next_index << "\n";
        } else if (command[0] == "density") {
            out << std::setprecision(12) << 1.0 * keys.size() / v.size() << "\n";
        }
    }
    out.close();

    return 0;
}