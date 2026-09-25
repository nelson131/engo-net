#pragma once

#include "../client/tcp_client.hpp"
#include "engo_net.hpp"

class EngoClient : public EngoNet {
   public:
    EngoClient();

    void loop() override;

    void stop();

   private:
    std::unique_ptr<TCP_Client> tcpc;
};
