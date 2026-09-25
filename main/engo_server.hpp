#pragma once

#include <memory>
#include <thread>

#include "../server/internal_node.hpp"
#include "engo_net.hpp"

class EngoServer : public EngoNet {
   public:
    EngoServer();

    void loop() override;

   private:
    std::unique_ptr<InternalNode> internal_node;
    std::thread                   network_thread;

   private:
    void stop();
};
