#pragma once

#include <memory>

#include "../utils/pair.hpp"
#include "file.hpp"

namespace engo {

class FormedFile : public File {
   public:
    FormedFile(const std::string& path);

    void load() override;

    std::string get(const engo::Pair<std::string, std::string>& fk);

   private:
    typedef std::unordered_map<std::string, std::string> line;

    std::unordered_map<std::string, line> content;
};

}  // namespace engo
