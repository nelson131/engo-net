#include "filesystem.hpp"

#include <filesystem>

using namespace engo;

bool filesystem::init() {
    const std::string home = std::string(getenv("HOME"));
    if (home.empty()) return 0;

    // logging
    std::string main_dir = "/.local/share/engo-net";
    if (!std::filesystem::exists(home + main_dir))
        std::filesystem::create_directory(home + main_dir);

    // config
    main_dir = "/.config/engo-net";
    if (!std::filesystem::exists(home + main_dir))
        std::filesystem::create_directory(home + main_dir);

    return 1;
}

std::string filesystem::get_home_path() { return std::string(getenv("HOME")); }

std::string filesystem::get_logging_dir() {
    return get_home_path() + "/.local/share/engo-net";
}

std::string filesystem::get_config_dir() {
    return get_home_path() + "/.config/engo-net";
}
