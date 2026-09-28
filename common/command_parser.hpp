#pragma once

#include <string>
#include <vector>

#include "command_type.hpp"

struct Command {
    CommandType              type;
    std::vector<std::string> args;
};

class CommandParser {
   public:
    CommandParser();

    Command parse(const std::string& input);

   private:
    CommandType convert_type(const std::string& cmd) const;
};
