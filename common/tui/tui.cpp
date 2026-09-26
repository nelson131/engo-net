#include "tui.hpp"

#include <iostream>

TUI::TUI(const engo::Pair<size_t, size_t>& screen_meta, Config& config)
    : buf(screen_meta.x, screen_meta.y), config(config), state(0) {
    sep = std::string(screen_meta.x, '_');
}

void TUI::render() {}

const std::string& TUI::get_sep() const noexcept { return sep; }

int TUI::get_state() const noexcept { return state; }

void TUI::draw_state() {}

void TUI::make_header() {}
