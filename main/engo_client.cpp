#include "engo_client.hpp"

#include <iostream>

EngoClient::EngoClient(size_t wcols, size_t wrows)
    : EngoNet(),
      tui(
          engo::Pair<size_t, size_t>{wcols, wrows},
          [this](const std::string& cmd) { execute_cmd(cmd); }, get_logger()) {
    tui_thread = std::thread([this] {
        while (is_running()) {
            using namespace std::chrono_literals;
            tui.run();
            std::this_thread::sleep_for(16ms);
        }
    });
}

EngoClient::~EngoClient() { stop_overall(); }

void EngoClient::stop_overall() {
    stop_network();

    if (tui_thread.joinable()) {
        tui_thread.join();
    }
}

void EngoClient::stop_network() {
    if (user) {
        user->stop();
        user.reset();
    }

    if (network_thread.joinable()) {
        network_thread.join();
    }
}

void EngoClient::execute_cmd(const std::string& input) {
    Command cmd = command_parser.parse(input);

    switch (cmd.type) {
        case CommandType::EXIT:
            quit();
            break;
        case CommandType::HELP:
            break;
        case CommandType::STOP:
            stop_network();
            break;
        case CommandType::UNKNOWN:
            get_logger().tlog(Logger::ERROR, "unknown command");
            break;
    }
}
