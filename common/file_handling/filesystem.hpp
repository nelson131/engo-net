#pragma once

#include <string>

namespace engo {

namespace filesystem {

bool init();

std::string get_home_path();
std::string get_logging_dir();
std::string get_config_dir();

};  // namespace filesystem

};  // namespace engo
