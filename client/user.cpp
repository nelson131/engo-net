#include "user.hpp"

#include <iostream>

User::User(const std::string& addr, uint16_t port, Logger& logger)
    : logger(logger), tcpc(addr, port, logger) {
    size_t attempts = 0;
    while (!tcpc.connect()) {
        if (attempts >= 5)
            throw std::runtime_error("user failed to connect to the server");
        attempts++;
    }

    connection = std::make_unique<Connection>(tcpc.get_socket().get());
}

void User::run() {
    while (enabled) {
        if (!connection->recv()) {
            enabled = 0;
            break;
        }

        while (auto packet = connection->get_ready_packet()) {
            // TODO quite lloooool asf
            std::cout << "received a packet: " << std::endl;
            std::cout << "type: " << packet->header.type << std::endl;
            std::cout << "data: "
                      << std::string(packet->data.begin(), packet->data.end())
                      << std::endl;
        }
    }
}

void User::stop() noexcept { enabled = 0; }

bool User::send(const std::string& message) {
    engo::Packet packet(engo::MESSAGE,
                        std::vector<uint8_t>(message.begin(), message.end()));

    return connection->send(packet);
}

bool User::send(const std::vector<std::string>& message, size_t arg) {
    if (arg >= message.size()) return 0;

    std::string msg = "";
    for (size_t i = 0; i < message.size(); i++) {
        if (i > 1) msg += " ";

        msg += message[i];
    }

    return send(msg);
}

bool User::is_enabled() const noexcept { return enabled; }
