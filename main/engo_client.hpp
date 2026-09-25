#pragma once

#include "../client/user.hpp"
#include "engo_net.hpp"

class EngoClient : public EngoNet {
   public:
    EngoClient();

    void loop() override;

    void stop();

   private:
    std::unique_ptr<User> user;
};
