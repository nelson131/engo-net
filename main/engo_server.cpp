#include "engo_server.hpp"

#include <iostream>
#include <vector>

EngoServer::EngoServer() : EngoNet() {}

void EngoServer::loop() {
    std::string cmd = "";
    while (is_running()) {
        std::cout << "> ";
        std::getline(std::cin, cmd);
        std::vector<std::string> args = get_args(cmd);

        if (args[0] == "exit") {
            stop();
            quit();
        } else if (args[0] == "start") {
            if (!internal_node) {
                internal_node = std::make_unique<InternalNode>(
                    args[1], static_cast<uint16_t>(std::stoul(args[2])),
                    get_logger());

                network_thread = std::thread([this] { internal_node->run(); });

                std::cout << "server started on: " << args[1] << ", port: "
                          << static_cast<uint16_t>(std::stoul(args[2]))
                          << std::endl;
            }
        } else if (args[0] == "stop") {
            stop();
        }
    }

    if (network_thread.joinable()) network_thread.join();
}

void EngoServer::stop() {
    if (internal_node) {
        internal_node->stop();
    }

    if (network_thread.joinable()) {
        network_thread.join();
    }

    internal_node.reset();
}
