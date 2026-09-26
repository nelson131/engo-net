#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../common/utils/pair.hpp"

enum ServerStatus { SHUTDOWN, RUNNING, STOPPED };

struct ServerState {
    ServerStatus status = SHUTDOWN;
    std::string  addr = "";
    uint16_t     port = 0;

    std::vector<engo::Pair<std::string, uint16_t>> clients;

    const char* status_msgs[3] = {"SHUTDOWN", "RUNNING", "STOPPED"};
};
