#pragma once

#include "../logger.hpp"
#include "rect.hpp"
#include "tui.hpp"

class ClientTUI : public TUI {
   public:
    ClientTUI(const engo::Pair<size_t, size_t>& screen_meta, Config& config,
              Logger& logger);

    void render() override;

   private:
    enum FocusState { LIST, CHAT };

   private:
    Logger& logger;

    FocusState            focus_state;
    std::unique_ptr<Rect> focus_rect;

   private:
    void draw_state() override;
    void make_header() override;
};
