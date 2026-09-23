#include "filesystem.hpp"

#include <filesystem>

using namespace engo;

void filesystem::init() {
    const std::string home = std::string(getenv("HOME"));
    if (home.empty()) throw std::runtime_error("failed to get home dir");

    // logging
    std::string main_dir = "/.local/share/engo-net";
    if (!std::filesystem::exists(home + main_dir))
        std::filesystem::create_directory(home + main_dir);

    // config
    main_dir = "/.config/engo-net";
    if (!std::filesystem::exists(home + main_dir))
        std::filesystem::create_directory(home + main_dir);
}

std::string filesystem::get_home_path() { return std::string(getenv("HOME")); }

std::string filesystem::get_logging_dir(bool with_home) {
    std::string path = "/.local/share/engo-net";
    if (with_home) return get_home_path() + path;
    return path;
}

std::string filesystem::get_config_dir(bool with_home) {
    std::string path = "/.config/engo-net";
    if (with_home) return get_home_path() + path;
    return path;
}
