#pragma once

#include <memory>

#include "../common/command_parser.hpp"
#include "../server/internal_node.hpp"
#include "../server/server_state.hpp"
#include "../server/tui/server_tui.hpp"
#include "engo_net.hpp"

class EngoServer : public EngoNet {
   public:
    EngoServer(size_t wcols, size_t wrows);
    ~EngoServer();

   private:
    std::unique_ptr<InternalNode> internal_node;

    ServerTUI     tui;
    ServerState   state;
    CommandParser command_parser;

   private:
    void stop_overall() override;
    void stop_network() override;

    void execute_cmd(const std::string& input);
};
