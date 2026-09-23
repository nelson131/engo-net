#pragma once

#include <string_view>

#include "engo_client.hpp"
#include "engo_server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) throw std::logic_error("usage: engo-net <client:server>");

    std::string_view mode = argv[1];

    if (mode == "client") {
        EngoClient engo_client{};
        while (engo_client.is_running()) {
        }
    }

    if (mode == "server") {
        EngoServer engo_server{};
        while (engo_server.is_running()) {
        }
    }

    return 0;
}
