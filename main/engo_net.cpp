#include "engo_net.hpp"

EngoNet::EngoNet() : run(1) {
    engo::filesystem::init();

    std::string log_file_name = "engo.log";
    logger = std::make_unique<Logger>(engo::filesystem::get_logging_dir(0) +
                                      log_file_name);

    std::string cfg_file_name = "config.engo";
    config = std::make_unique<Config>(engo::filesystem::get_config_dir(1) +
                                      cfg_file_name);
}

void EngoNet::loop() {}

void EngoNet::quit() noexcept { run = 0; }

bool EngoNet::is_running() const noexcept { return run; }

std::vector<std::string> EngoNet::get_args(const std::string& input) const {
    std::istringstream       stream(input);
    std::string              arg;
    std::vector<std::string> args;

    while (stream >> arg) {
        args.push_back(arg);
    }

    return args;
}

Logger& EngoNet::get_logger() const noexcept { return *logger; }

Config& EngoNet::get_config() const noexcept { return *config; }
