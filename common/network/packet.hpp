#pragma once

#include <cstdint>
#include <vector>

namespace engo {

typedef uint16_t PacketType;

struct PacketHeader {
    PacketType type;
    uint16_t   payload_size;
};

struct Packet {
    PacketHeader         header;
    std::vector<uint8_t> data;
};

};  // namespace engo
