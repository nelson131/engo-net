#include "tui.hpp"

#include <iostream>

TUI::TUI(const engo::Pair<size_t, size_t>& screen_meta)
    : buf(screen_meta.x, screen_meta.y) {
    sep = std::string(screen_meta.x, '_');

    std::cout << "\033[?25l";
}

TUI::~TUI() { std::cout << "\033[?25h"; }

void TUI::run() {}

const std::string& TUI::get_sep() const noexcept { return sep; }

void TUI::render() {}

void TUI::handle_input() {}

void TUI::make_header() {}
