#pragma once

#include <memory>

#include "../../server/server_state.hpp"
#include "console.hpp"
#include "rect.hpp"
#include "tui.hpp"

class ServerTUI : public TUI {
   public:
    ServerTUI(const engo::Pair<size_t, size_t>& screen_meta, ServerState& state,
              Config& config);

    void render() override;

   private:
    void draw_state() override;
    void make_header() override;

   private:
    ServerState& state;

    std::unique_ptr<Rect> rect;
    std::string           rect_floor;

    std::unique_ptr<Console> console;
};
