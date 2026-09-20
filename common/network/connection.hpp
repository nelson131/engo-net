#pragma once

#include <unistd.h>

#include <cstdint>
#include <vector>

#include "io_result.hpp"

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

    IOResult send();
    IOResult recv();

    int  get_socket() const noexcept;
    bool is_closed() const noexcept;

   private:
    int m_socket;

    std::vector<uint8_t> send_buf;
    std::vector<uint8_t> recv_buf;

    bool closed;
};
