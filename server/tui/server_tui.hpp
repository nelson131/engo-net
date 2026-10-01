#pragma once

#include <memory>
#include <mutex>
#include <queue>

#include "../../common/logger.hpp"
#include "../../common/tui/console.hpp"
#include "../../common/tui/input_handler.hpp"
#include "../../common/tui/rect.hpp"
#include "../../common/tui/tui.hpp"
#include "../server_state.hpp"

class ServerTUI : public TUI {
   public:
    using CommandCallback = std::function<void(const std::string&)>;

   public:
    ServerTUI(const engo::Pair<size_t, size_t>& screen_meta, ServerState& state,
              CommandCallback cmd_callback, Logger& logger);

    void run() override;

    void send_help_msg();

   private:
    ServerState& state;
    Logger&      logger;

    CommandCallback cmd_callback;
    InputHandler    input_handler;

    std::unique_ptr<Console> console;

    std::unique_ptr<Rect> rect;
    std::string           rect_floor;

   private:
    void render() override;
    void handle_input() override;

    void sumbit_console();
};
