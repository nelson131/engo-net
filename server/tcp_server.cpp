#include "tcp_server.hpp"

TCP_Server::TCP_Server(const std::string& m_addr, uint16_t port, Logger& logger)
    : m_addr(m_addr),
      port(port),
      s_addr(),
      m_socket(std::make_unique<Socket>()),
      logger(logger) {
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(m_addr.c_str());
    s_addr.sin_port = htons(port);

    if (!m_socket->make_non_blocking())
        throw std::runtime_error("failed to make server socket non blocking");

    int opt = 1;
    if (setsockopt(m_socket->get(), SOL_SOCKET, SO_REUSEADDR, &opt,
                   sizeof(opt)) == -1)
        throw std::runtime_error("failed to set sock opt");
}

bool TCP_Server::bind() {
    return ::bind(m_socket->get(), (struct sockaddr*)&s_addr, sizeof(s_addr)) ==
           0;
}

bool TCP_Server::listen() { return ::listen(m_socket->get(), SOMAXCONN) == 0; }

Socket& TCP_Server::get_socket() const noexcept { return *m_socket; }
