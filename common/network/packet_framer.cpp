#include "packet_framer.hpp"

#include <netinet/in.h>

PacketFramer::PacketFramer() : queue() {}

void PacketFramer::parse_raw(std::vector<uint8_t>& buf) {
    while (buf.size() >= sizeof(engo::PacketHeader)) {
        engo::PacketHeader* header =
            reinterpret_cast<engo::PacketHeader*>(buf.data());

        uint16_t payload_size = ntohs(header->payload_size);
        size_t   packet_size = payload_size + sizeof(engo::PacketHeader);

        if (buf.size() < packet_size) break;

        std::unique_ptr<engo::Packet> fresh_packet =
            std::make_unique<engo::Packet>();

        fresh_packet->header.type = ntohs(header->type);
        fresh_packet->header.payload_size = payload_size;

        fresh_packet->data.resize(packet_size);
        std::copy(buf.begin(), buf.begin() + packet_size,
                  fresh_packet->data.begin());

        queue.push(fresh_packet);

        buf.erase(buf.begin(), buf.begin() + packet_size);
    }
}

std::unique_ptr<engo::Packet> PacketFramer::pop_queue() {
    if (queue.empty()) return nullptr;
    std::unique_ptr<engo::Packet> p = std::move(queue.front());
    queue.pop();
    return p;
}
