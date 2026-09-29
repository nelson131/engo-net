#include "server_tui.hpp"

ServerTUI::ServerTUI(const engo::Pair<size_t, size_t>& screen_meta,
                     ServerState& state, CommandCallback cmd_callback,
                     Logger& logger)
    : TUI(screen_meta),
      state(state),
      cmd_callback(std::move(cmd_callback)),
      logger(logger) {
    buf.clear();

    size_t rect_w = (size_t)screen_meta.x * 0.25;
    rect = std::make_unique<Rect>(
        engo::Pair<size_t, size_t>{0, 3},
        engo::Pair<size_t, size_t>{rect_w, screen_meta.y - 6});

    rect_floor = std::string(rect->get_size().x - 2, '-');

    console = std::make_unique<Console>(
        Rect{{rect->get_vec().x + rect->get_size().x + 1, rect->get_vec().y},
             {screen_meta.x - rect->get_size().x - 1, screen_meta.y - 6}});
}

void ServerTUI::run() {
    handle_input();
    render();
}

void ServerTUI::send_help_msg() {
    std::string msg =
        "exit -> quit from application, help -> send this message, start "
        "<ip_addr> <port> -> start the server, stop -> stop the network side";

    console->get_message_list().add("server", msg);
}

void ServerTUI::add_log(const std::string& type, const std::string& message) {
    std::lock_guard lock(log_mutex);
    log_queue.push(type + " -> " + message);
}

void ServerTUI::render() {
    buf.clear();
    process_logs();
    make_header();

    rect->draw(buf);

    size_t x = rect->get_vec().x + 1;
    size_t y = rect->get_vec().y + 1;

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

    buf.render();
}

void ServerTUI::handle_input() {
    int key = input_handler.poll();
    if (key == InputHandler::NONE) return;

    if (key == InputHandler::ENTER1 || key == InputHandler::ENTER2) {
        sumbit_console();
        return;
    }

    if (key == InputHandler::BACKSPACE) {
        console->get_input().backspace();
        return;
    }

    if (key >= 32 && key <= 126) {
        console->get_input().put(key);
        return;
    }
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

void ServerTUI::sumbit_console() {
    std::string cmd = console->sumbit_input();
    if (cmd_callback) {
        cmd_callback(cmd);
    }
}

void ServerTUI::process_logs() {
    std::lock_guard lock(log_mutex);

    while (!log_queue.empty()) {
        console->get_message_list().add("server", log_queue.front());
        log_queue.pop();
    }
}
