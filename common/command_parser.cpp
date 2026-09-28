#include "command_parser.hpp"

#include <sstream>
#include <unordered_map>

CommandParser::CommandParser() {}

Command CommandParser::parse(const std::string& input) {
    if (input.empty()) return {UNKNOWN, {}};

    Command res{};

    std::istringstream ss(input);
    std::string        arg;

    while (ss >> arg) {
        if (res.args.size() == 0) {
            res.type = convert_type(arg);
            if (res.type == UNKNOWN) return res;
        }

        res.args.push_back(arg);
    }

    return res;
}

CommandType CommandParser::convert_type(const std::string& cmd) const {
    static std::unordered_map<std::string, CommandType> map = {{"exit", EXIT},
                                                               {"help", HELP}};

    auto it = map.find(cmd);
    if (it != map.end()) {
        return it->second;
    }

    return UNKNOWN;
}
