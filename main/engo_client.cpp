#include "engo_client.hpp"

#include <iostream>

EngoClient::EngoClient() : EngoNet() {}

void EngoClient::loop() {
    while (is_running()) {
        std::cout << "> ";
        std::string cmd = "";
        std::getline(std::cin, cmd);
        std::vector<std::string> args = get_args(cmd);

        if (args.empty()) continue;

        if (args[0] == "exit") {
            stop();
            quit();
        } else if (args[0] == "connect" && args.size() == 3) {
            if (!tcpc) {
                std::string& addr = args[1];
                uint16_t     port = static_cast<uint16_t>(std::stoul(args[2]));

                tcpc = std::make_unique<TCP_Client>(addr, port, get_logger());
                while (!tcpc->connect()) {
                    std::cout << "trying to connect to: " << addr
                              << ", port: " << port << std::endl;
                }

                std::cout << "connected!" << std::endl;
            }
        } else if (args[0] == "stop") {
            stop();
        }
    }
}

void EngoClient::stop() {
    if (tcpc) {
        tcpc.reset();
    }
}
