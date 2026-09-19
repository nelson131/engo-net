#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

class Socket {
   public:
    Socket();
    ~Socket();

    const int get() const noexcept;

   private:
    int m_socket;
};
