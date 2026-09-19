#include "socket.hpp"

#include <iostream>

Socket::Socket() : m_socket() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) throw std::runtime_error("failed to create the socket");
}

Socket::~Socket() {
    if (m_socket > 0) close(m_socket);
}

const int Socket::get() const noexcept { return m_socket; }
