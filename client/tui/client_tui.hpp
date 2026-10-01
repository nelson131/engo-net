#pragma once

#include "../../common/logger.hpp"
#include "../../common/tui/console.hpp"
#include "../../common/tui/input_handler.hpp"
#include "../../common/tui/rect.hpp"
#include "../../common/tui/tui.hpp"

class ClientTUI : public TUI {
   public:
    using CommandCallback = std::function<void(const std::string&)>;
    enum FocusState { GENERAL_CHATS, ENGO_CHAT, MESSAGES };

   public:
    ClientTUI(const engo::Pair<size_t, size_t>& screen_meta,
              CommandCallback cmd_callback, Logger& logger);

    void run() override;

    void send_help_msg();

   private:
    engo::Pair<size_t, size_t> screen_meta;

    Logger& logger;

    CommandCallback cmd_callback;
    InputHandler    input_handler;

    std::unique_ptr<Console> console;

    std::unique_ptr<Rect> chats_rect;
    std::string           rect_floor;

    FocusState focus_state;

   private:
    void render() override;
    void handle_input() override;

    void make_chats_section();
};
