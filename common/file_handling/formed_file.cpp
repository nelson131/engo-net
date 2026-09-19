#include "formed_file.hpp"

#include <fstream>
#include <iostream>

using namespace engo;

FormedFile::FormedFile(const std::string& path) : File(path), content() {}

void FormedFile::load() {
    const std::string& path = get_path();
    if (path.empty()) throw std::logic_error("path is empty");

    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("failed to open the file");

    bool        has_obj = false;
    std::string title = "";
    line        map_line{};

    std::string line = "";
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line[0] == ';') {
            content[title] = map_line;
            map_line.clear();
            has_obj = false;
            continue;
        }
        if (line[0] == '[') {
            line.erase(0, 1);
            line.erase(line.size() - 1);
            title = line;
            has_obj = true;
            continue;
        }

        if (has_obj) {
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                map_line[key] = value;
                continue;
            }
        }
    }
}

std::string FormedFile::get(const engo::Pair<std::string, std::string>& fk) {
    if (fk.x.empty() || fk.y.empty()) return "idk";

    auto iter = content.find(fk.x);
    if (iter != content.end()) {
        auto it = iter->second.find(fk.y);
        if (it != iter->second.end()) return it->second;
    }

    return "idk";
}
