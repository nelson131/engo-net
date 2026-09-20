#include "internal_node.hpp"

#include <sys/epoll.h>

InternalNode::InternalNode(const std::string& m_addr, uint16_t port,
                           Logger& logger)
    : tcps(std::make_unique<TCP_Server>(m_addr, port, logger)),
      logger(logger),
      epoll_fd(-1),
      events(),
      enabled(1) {
    std::string msg = m_addr + "/" + std::to_string(port);
    if (!tcps->bind())
        throw std::runtime_error("failed to bind the internal node: " + msg);

    if (!tcps->listen())
        throw std::runtime_error("failed to listen in the internal node: " +
                                 msg);

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
        throw std::runtime_error("failed to create epoll: " + msg);

    epoll_event event{};
    event.events = EPOLLIN | EPOLLRDHUP;
    event.data.fd = tcps->get_socket().get();
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tcps->get_socket().get(), &event) ==
        -1)
        throw std::runtime_error("failed to epoll ctl: " + msg);

    events.resize(MAX_EVENTS);

    logger.log(Logger::INFO, "internal node started on: " + msg);
}

InternalNode::~InternalNode() {
    for (int fd : clients) {
        close(fd);
    }

    if (epoll_fd >= 0) {
        close(epoll_fd);
    }
}

void InternalNode::run() {
    while (enabled) {
        int num_events = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        if (num_events == -1) {
            enabled = 0;
            logger.log(Logger::ERROR,
                       "failed to wait for events in the internal node");
        }

        for (size_t i = 0; i < num_events; i++) {
            if (events[i].data.fd == tcps->get_socket().get()) {
                while (1) {
                    int client_fd = receive();
                    if (client_fd == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                        if (errno == EINTR) continue;

                        logger.log(Logger::ERROR,
                                   "failed to accept the client connection");
                        break;
                    }

                    epoll_event event{};
                    event.events = EPOLLIN | EPOLLRDHUP;
                    event.data.fd = client_fd;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) ==
                        -1) {
                        close(client_fd);
                        logger.log(Logger::ERROR,
                                   "failed to add the client fd to the epoll");
                        continue;
                    }

                    clients.emplace(client_fd);
                }
            } else {
                // TODO recv
            }
        }
    }
}

bool InternalNode::is_enabled() const noexcept { return enabled; }

int InternalNode::receive() {
    sockaddr_in client_addr{};
    socklen_t   client_addr_len = sizeof(client_addr);
    return accept4(tcps->get_socket().get(), (struct sockaddr*)&client_addr,
                   &client_addr_len, SOCK_NONBLOCK | SOCK_CLOEXEC);
}
