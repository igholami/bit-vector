//
// Created by Iman Gholami on 4/9/24.
//

#include <sstream>
#include <fstream>
#include "command_reader.h"

namespace bitvector {
    command_reader::command_reader(std::string filename) {
        std::ifstream file(filename);
        this->commands.resize(0);
        while(not file.eof()) {
            std::string line;
            std::getline(file, line);
            std::vector<std::string> command;
            std::string token;
            std::istringstream tokenStream(line);
            while (std::getline(tokenStream, token, ' ')) {
                command.push_back(token);
            }
            if (command.size() > 0)
                this->commands.push_back(command);
        }
    }

    std::vector<std::vector<std::string>> command_reader::get_commands() {
        return this->commands;
    }
} // bitvector