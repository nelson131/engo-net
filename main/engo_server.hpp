#pragma once

#include <memory>

#include "../common/tui/server_tui.hpp"
#include "../server/internal_node.hpp"
#include "../server/server_state.hpp"
#include "engo_net.hpp"

class EngoServer : public EngoNet {
   public:
    EngoServer(size_t wcols, size_t wrows);

    void loop() override;

   private:
    std::unique_ptr<InternalNode> internal_node;

    ServerTUI   tui;
    ServerState state;

   private:
    void stop();
};
