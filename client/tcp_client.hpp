#pragma once

#include <memory>

#include "../common/logger.hpp"
#include "../common/network/socket.hpp"

class TCP_Client {
   public:
    TCP_Client(const std::string& m_addr, uint64_t port, Logger& logger);

    bool conn();

   private:
    Logger& logger;

    std::string m_addr;
    uint64_t    port;
    sockaddr_in s_addr;

    std::unique_ptr<Socket> m_socket;
};
