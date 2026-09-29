#pragma once

#include "../../common/logger.hpp"
#include "../../common/tui/rect.hpp"
#include "../../common/tui/tui.hpp"

class ClientTUI : public TUI {
   public:
    enum FocusState { CHATS, MESSAGES };

   public:
    ClientTUI(const engo::Pair<size_t, size_t>& screen_meta, Config& config,
              Logger& logger);

    void render() override;

   private:
    Logger& logger;

    std::unique_ptr<Rect> chats_rect;
    std::string           rect_floor;

    FocusState focus_state;

   private:
    void make_header() override;
};
