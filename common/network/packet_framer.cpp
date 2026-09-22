#include "packet_framer.hpp"

#include <netinet/in.h>

PacketFramer::PacketFramer() : queue() {}

void PacketFramer::parse_raw(std::vector<uint8_t>& buf) {
    std::unique_ptr<engo::Packet> fresh_packet =
        std::make_unique<engo::Packet>();

    while (buf.size() >= sizeof(engo::PacketHeader)) {
        engo::PacketHeader* header =
            reinterpret_cast<engo::PacketHeader*>(buf.data());

        uint16_t payload_size = ntohs(header->payload_size);
        size_t   packet_size = payload_size + sizeof(engo::PacketHeader);

        if (buf.size() < packet_size) break;

        fresh_packet->header.type = ntohs(header->type);
        fresh_packet->header.payload_size = payload_size;

        fresh_packet->data.resize(packet_size);
        std::copy(buf.begin(), buf.begin() + packet_size,
                  fresh_packet->data.begin());

        buf.erase(buf.begin(), buf.begin() + packet_size);
    }

    queue.push(fresh_packet);
}

std::unique_ptr<engo::Packet> PacketFramer::pop_queue() {
    std::unique_ptr<engo::Packet> p = std::move(queue.front());
    queue.pop();
    return p;
}
