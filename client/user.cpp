#include "user.hpp"

#include <iostream>

User::User(const std::string& addr, uint16_t port, MessageCallback msg_callback,
           Logger& logger)
    : logger(logger),
      tcpc(addr, port, logger),
      enabled(1),
      msg_callback(std::move(msg_callback)) {
    size_t attempts = 0;
    while (!tcpc.connect()) {
        if (attempts >= 5)
            throw std::runtime_error("user failed to connect to the server");
        attempts++;
    }

    tcpc.get_socket().make_non_blocking();
    connection = std::make_unique<Connection>(tcpc.get_socket().get());
}

void User::run() {
    while (enabled) {
        if (!connection->recv()) {
            enabled = 0;
            break;
        }

        while (auto packet = connection->get_ready_packet()) {
            if (msg_callback &&
                packet->header.type == engo::PacketType::MESSAGE) {
                msg_callback(
                    std::string(packet->data.begin(), packet->data.end()));
            }
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
    for (size_t i = arg; i < message.size(); i++) {
        if (i > 1) msg += " ";

        msg += message[i];
    }

    return send(msg);
}

bool User::is_enabled() const noexcept { return enabled; }
