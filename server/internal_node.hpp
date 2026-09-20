#pragma once

#include <sys/epoll.h>

#include <memory>
#include <unordered_set>
#include <vector>

#include "../common/logger.hpp"
#include "tcp_server.hpp"

#define MAX_EVENTS 33

class InternalNode {
   public:
    InternalNode(const std::string& m_addr, uint16_t port, Logger& logger);
    ~InternalNode();

    void run();

    bool is_enabled() const;

   private:
    Logger& logger;

    std::unique_ptr<TCP_Server> tcps;

    int                      epoll_fd;
    std::vector<epoll_event> events;

    std::unordered_set<int> clients;

    bool enabled;
};
