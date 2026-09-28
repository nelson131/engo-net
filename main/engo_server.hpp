#pragma once

#include <memory>

#include "../common/command_parser.hpp"
#include "../common/tui/input_handler.hpp"
#include "../common/tui/server_tui.hpp"
#include "../server/internal_node.hpp"
#include "../server/server_state.hpp"
#include "engo_net.hpp"

class EngoServer : public EngoNet {
   public:
    EngoServer(size_t wcols, size_t wrows);
    ~EngoServer();

    void loop() override;

   private:
    std::unique_ptr<InternalNode> internal_node;

    ServerTUI     tui;
    ServerState   state;
    InputHandler  input_handler;
    CommandParser command_parser;

   private:
    void handle_input() override;
    void stop();

    void execute_cmd(const std::string& input);

    std::string get_help_msg() const noexcept;
};
