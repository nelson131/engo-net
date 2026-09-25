#pragma once

#include "../common/network/connection.hpp"
#include "tcp_client.hpp"

class User {
   public:
    User(const std::string& addr, uint16_t port, Logger& logger);

    void run();
    void stop() noexcept;

    bool send(const std::string& message);
    bool send(const std::vector<std::string>& message, size_t arg);

    bool is_enabled() const noexcept;

   private:
    Logger& logger;

    bool enabled;

    TCP_Client                  tcpc;
    std::unique_ptr<Connection> connection;
};
