#pragma once

#include <string>
#include <unordered_map>

namespace engo {

class File {
   public:
    File(const std::string& path) : path(path), home(getenv("HOME")) {}

    virtual void load() {}
    virtual void write() {}

    const std::string& get_home() const noexcept { return home; }

    const std::string& get_path() const noexcept { return path; }

   private:
    const std::string home;
    const std::string path;
};

}  // namespace engo
