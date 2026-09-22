#pragma once

#include <memory>
#include <queue>

#include "packet.hpp"

class PacketFramer {
   public:
    PacketFramer();

    void parse_raw(std::vector<uint8_t>& buf);

    std::unique_ptr<engo::Packet> pop_queue();

   private:
    std::queue<std::unique_ptr<engo::Packet>> queue;
};
