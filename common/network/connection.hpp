#pragma once

#include <arpa/inet.h>
#include <unistd.h>

#include <cstdint>
#include <vector>

#include "packet.hpp"

#define DEF_BUF_SIZE 1024

class Connection {
   public:
    Connection(int m_socket);
    ~Connection();

    void close() noexcept;

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    Connection(Connection&& other) noexcept;
    Connection& operator=(Connection&& other) noexcept;

    bool send(const engo::Packet& packet);
    bool recv();

    int  get_socket() const noexcept;
    bool is_closed() const noexcept;

   private:
    int m_socket;

    std::vector<uint8_t> recv_buf;

    bool closed;
};
