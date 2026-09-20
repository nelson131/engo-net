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

bool TCP_Server::make_bind() {
    return bind(m_socket->get(), (struct sockaddr*)&s_addr, sizeof(s_addr)) ==
           0;
}

bool TCP_Server::listening() { return listen(m_socket->get(), SOMAXCONN) == 0; }

int TCP_Server::receive() {
    sockaddr_in client_addr;
    socklen_t   client_addr_len = sizeof(client_addr);
    return accept4(m_socket->get(), (struct sockaddr*)&client_addr,
                   &client_addr_len, SOCK_NONBLOCK | SOCK_CLOEXEC);
}

Socket& TCP_Server::get_socket() const { return *m_socket; }
