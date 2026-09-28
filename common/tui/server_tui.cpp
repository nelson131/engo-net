#include "server_tui.hpp"

ServerTUI::ServerTUI(const engo::Pair<size_t, size_t>& screen_meta,
                     ServerState& state, Config& config)
    : TUI(screen_meta, config), state(state) {
    buf.clear();

    size_t rect_w = (size_t)screen_meta.x * 0.25;
    rect = std::make_unique<Rect>(
        engo::Pair<size_t, size_t>{0, 3},
        engo::Pair<size_t, size_t>{rect_w, screen_meta.y - 6});

    rect_floor = std::string(rect->get_size().x - 2, '-');

    console = std::make_unique<Console>(
        Rect{{rect->get_vec().x + rect->get_size().x + 1, rect->get_vec().y},
             {screen_meta.x - rect->get_size().x, screen_meta.y - 6}});
}

void ServerTUI::render() {
    buf.clear();
    make_header();
    draw_state();
    buf.render();
}

void ServerTUI::write_console(char c) { console->get_input().put(c); }

void ServerTUI::write_console(const std::string& author,
                              const std::string& msg) {
    console->get_message_list().add(author, msg);
}

void ServerTUI::pop_console() { console->get_input().backspace(); }

std::string ServerTUI::sumbit_console() { return console->sumbit_input(); }

void ServerTUI::draw_state() {
    rect->draw(buf);

    size_t x = 1;
    size_t y = 4;

    // Server status >>>
    // 1 section: status, addr, port
    buf.put(engo::Pair<size_t, size_t>{x, y++},
            "state: " + std::string(state.status_msgs[state.status]));
    buf.put(engo::Pair<size_t, size_t>{x, y++}, "address: " + state.addr);
    buf.put(engo::Pair<size_t, size_t>{x, y},
            "port: " + std::to_string(state.port));
    y += 2;

    // 2 section: clients, their addrs and ports
    buf.put(engo::Pair<size_t, size_t>{x, y++}, rect_floor, COLOR_DEFAULT,
            COLOR_DEFAULT, STYLE_BOLD);
    buf.put(engo::Pair<size_t, size_t>{x, y++},
            "clients: " + std::to_string(state.clients.size()));
    for (size_t i = 0; i < state.clients.size(); i++) {
        buf.put(engo::Pair<size_t, size_t>{x, y++},
                state.clients[i].x + ":" + std::to_string(state.clients[i].y) +
                    ": connected");
    }
    y++;
    buf.put(engo::Pair<size_t, size_t>{x, y++}, rect_floor, COLOR_DEFAULT,
            COLOR_DEFAULT, STYLE_BOLD);

    // Console >>
    console->draw(buf);
}

void ServerTUI::make_header() {
    // TOP SIDE
    std::string title = CONFIG_ENGO_NAME + std::string(" ") +
                        CONFIG_ENGO_VERSION + std::string(" -> server TUI");
    buf.put(engo::Pair<size_t, size_t>{0, 1}, title, COLOR_CYAN, COLOR_DEFAULT,
            STYLE_BOLD);
    buf.put(engo::Pair<size_t, size_t>{0, 2}, get_sep(), COLOR_DEFAULT,
            COLOR_DEFAULT, STYLE_BOLD);

    // BOTTOM SIDE
    buf.put(engo::Pair<size_t, size_t>{0, buf.get_wrows() - 3}, get_sep(),
            COLOR_DEFAULT, COLOR_DEFAULT, STYLE_BOLD);
}
