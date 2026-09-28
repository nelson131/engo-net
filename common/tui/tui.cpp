#include "tui.hpp"

#include <iostream>

TUI::TUI(const engo::Pair<size_t, size_t>& screen_meta, Config& config)
    : buf(screen_meta.x, screen_meta.y), config(config) {
    sep = std::string(screen_meta.x, '_');

    std::cout << "\033[?25l";
}

TUI::~TUI() { std::cout << "\033[?25h"; }

void TUI::render() {}

const std::string& TUI::get_sep() const noexcept { return sep; }

void TUI::draw_state() {}

void TUI::make_header() {}
