#include "connection.hpp"

#include <sys/socket.h>

#include <cerrno>

#include "io_result.hpp"

Connection::Connection(int m_socket) : m_socket(m_socket), closed(0) {
    send_buf.resize(DEF_BUF_SIZE);
    recv_buf.resize(DEF_BUF_SIZE);
}

Connection::~Connection() { close(); }

void Connection::close() noexcept {
    if (m_socket >= 0) {
        ::close(m_socket);
        m_socket = -1;
    }

    closed = 1;
}

Connection::Connection(Connection&& other) noexcept
    : m_socket(other.m_socket),
      recv_buf(std::move(other.recv_buf)),
      send_buf(std::move(other.send_buf)),
      closed(other.closed) {
    other.m_socket = -1;
    other.closed = 1;
}

Connection& Connection::operator=(Connection&& other) noexcept {
    if (this == &other) return *this;

    close();

    m_socket = other.m_socket;
    recv_buf = std::move(other.recv_buf);
    send_buf = std::move(other.send_buf);
    closed = other.closed;

    other.m_socket = -1;
    other.closed = true;

    return *this;
}

IOResult Connection::send() {}

IOResult Connection::recv() {
    while (1) {
        ssize_t val = ::recv(m_socket, recv_buf.data(), recv_buf.size(), 0);
        if (val > 0) return IOResult::SUCCESS;
        if (val == 0) {
            close();
            return IOResult::CLOSED;
        }

        if (errno == EINTR) continue;

        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return IOResult::WOULDBLOCK;
        }

        close();
        return IOResult::ERROR;
    }
}

int Connection::get_socket() const noexcept { return m_socket; }

bool Connection::is_closed() const noexcept { return closed; }
