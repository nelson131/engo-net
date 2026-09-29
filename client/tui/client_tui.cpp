#include "client_tui.hpp"

ClientTUI::ClientTUI(const engo::Pair<size_t, size_t>& screen_meta,
                     Config& config, Logger& logger)
    : TUI(screen_meta), logger(logger) {
    buf.clear();

    size_t rect_w = (size_t)screen_meta.x * 0.25;
    chats_rect = std::make_unique<Rect>(
        engo::Pair<size_t, size_t>{0, 3},
        engo::Pair<size_t, size_t>{rect_w, screen_meta.y - 6});

    rect_floor = std::string(rect_w - 2, '2');
}

void ClientTUI::render() {
    buf.clear();
    make_header();

    chats_rect->draw(buf);

    // clients chats
    size_t x = chats_rect->get_vec().x + 1;
    size_t y = chats_rect->get_vec().y + 1;
    buf.put({x, y}, "engo-net =>", COLOR_BLUE, COLOR_DEFAULT, STYLE_BOLD);

    // chat lol

    buf.render();
}

void ClientTUI::make_header() {
    // TOP SIDE
    std::string title = CONFIG_ENGO_NAME + std::string(" ") +
                        CONFIG_ENGO_VERSION + std::string(" -> client TUI");
    buf.put(engo::Pair<size_t, size_t>{0, 1}, title, COLOR_CYAN, COLOR_DEFAULT,
            STYLE_BOLD);
    buf.put(engo::Pair<size_t, size_t>{0, 2}, get_sep(), COLOR_DEFAULT,
            COLOR_DEFAULT, STYLE_BOLD);

    // BOTTOM SIDE
    buf.put(engo::Pair<size_t, size_t>{0, buf.get_wrows() - 3}, get_sep(),
            COLOR_DEFAULT, COLOR_DEFAULT, STYLE_BOLD);
}
