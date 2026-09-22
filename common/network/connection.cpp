#include "connection.hpp"

#include <sys/socket.h>

#include <cerrno>

Connection::Connection(int m_socket) : m_socket(m_socket), closed(0) {
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
      closed(other.closed) {
    other.m_socket = -1;
    other.closed = 1;
}

Connection& Connection::operator=(Connection&& other) noexcept {
    if (this == &other) return *this;

    close();

    m_socket = other.m_socket;
    recv_buf = std::move(other.recv_buf);
    closed = other.closed;

    other.m_socket = -1;
    other.closed = true;

    return *this;
}

bool Connection::send(const engo::Packet& packet) {
    engo::Packet send_packet = packet;
    send_packet.header.type = htons(packet.header.type);
    send_packet.header.payload_size = htons(packet.header.payload_size);

    size_t total_size = sizeof(engo::PacketHeader) + packet.header.payload_size;
    size_t sent = 0;

    while (sent < total_size) {
        ssize_t val = ::send(m_socket, send_packet.data.data() + sent,
                             total_size - sent, 0);

        if (val < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
            return 0;
        }

        sent += val;
    }

    return 1;
}

bool Connection::recv() {
    char    temp[4096];
    ssize_t val = ::recv(m_socket, temp, sizeof(temp), 0);
    if (val <= 0) return 0;

    recv_buf.insert(recv_buf.end(), temp, temp + val);
    return 1;
}

std::unique_ptr<engo::Packet> Connection::get_ready_packet() {
    return packet_framer.pop_queue();
}

int Connection::get_socket() const noexcept { return m_socket; }

bool Connection::is_closed() const noexcept { return closed; }
