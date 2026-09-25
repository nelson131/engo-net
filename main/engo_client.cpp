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
            if (!user) {
                std::string& addr = args[1];
                uint16_t     port = static_cast<uint16_t>(std::stoul(args[2]));

                try {
                    user = std::make_unique<User>(addr, port, get_logger());
                } catch (const std::exception& e) {
                    std::cout << "failed to connect to the server: " << addr
                              << ", port: " << port << std::endl;
                    continue;
                }

                std::cout << "connected! -> " << addr << ", port: " << port
                          << std::endl;

                network_thread = std::thread([this] { user->run(); });
            }
        } else if (args[0] == "stop") {
            stop();
        } else if (args[0] == "send" && user) {
            if (!user->send(args, 1)) {
                std::cout << "failed to send the mssage" << std::endl;
            } else {
                std::cout << "GOOD" << std::endl;
            }
        }
    }

    if (network_thread.joinable()) network_thread.join();
}

void EngoClient::stop() {
    if (user) {
        user->stop();
    }

    if (network_thread.joinable()) {
        network_thread.join();
    }

    user.reset();
}
