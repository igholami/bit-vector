//
// Created by Iman Gholami on 4/9/24.
//

#ifndef CMSC701_A1_COMMAND_READER_H
#define CMSC701_A1_COMMAND_READER_H

#include <string>
#include <vector>

namespace bitvector {

    class command_reader {
    private:
        std::vector<std::vector<std::string>> commands;
    public:
        command_reader(std::string filename);

        std::vector<std::vector<std::string>> get_commands();
    };

} // bitvector

#endif //CMSC701_A1_COMMAND_READER_H
