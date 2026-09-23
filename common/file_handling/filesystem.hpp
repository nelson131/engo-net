#pragma once

#include <string>

namespace engo {

namespace filesystem {

void init();

std::string get_home_path();
std::string get_logging_dir(bool with_home);
std::string get_config_dir(bool with_home);

};  // namespace filesystem

};  // namespace engo
