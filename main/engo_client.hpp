#pragma once

#include "../client/user.hpp"
#include "../common/tui/client_tui.hpp"
#include "engo_net.hpp"

class EngoClient : public EngoNet {
   public:
    EngoClient(size_t wcols, size_t wrows);
    ~EngoClient();

    void loop() override;

    void stop();

   private:
    std::unique_ptr<User> user;

    ClientTUI tui;
};
