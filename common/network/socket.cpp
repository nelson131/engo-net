#include "socket.hpp"

#include <fcntl.h>

#include <iostream>

Socket::Socket() : m_socket(-1) {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) throw std::runtime_error("failed to create the socket");
}

Socket::~Socket() {
    if (m_socket >= 0) close(m_socket);
}

bool Socket::make_non_blocking() {
    int flags = fcntl(m_socket, F_GETFL, 0);
    if (flags == -1) return 0;

    return fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);
}

int Socket::get() const noexcept { return m_socket; }
