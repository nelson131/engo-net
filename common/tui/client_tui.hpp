#pragma once

#include "tui.hpp"

class ClientTUI : public TUI {
   public:
    ClientTUI(const engo::Pair<size_t, size_t>& screen_meta, Config& config);

    void render() override;

   private:
    void draw_state() override;
    void make_header() override;
};
