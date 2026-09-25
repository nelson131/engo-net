#pragma once

#include "engo_net.hpp"

class EngoClient : public EngoNet {
   public:
    EngoClient();

    void loop() override;
};
