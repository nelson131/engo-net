#include "engo_server.hpp"

EngoServer::EngoServer(size_t wcols, size_t wrows)
    : EngoNet(),
      tui(engo::Pair<size_t, size_t>{wcols, wrows}, state, get_config()) {
    enable_raw_mode();
}

EngoServer::~EngoServer() {
    stop();
    disable_raw_mode();
}

void EngoServer::loop() {
    while (is_running()) {
        handle_input();
        tui.render();
    }
}

void EngoServer::handle_input() {
    int key = input_handler.poll();
    if (key == 'q') {
        quit();
        return;
    }

    tui.write_console(key);
}

void EngoServer::stop() {
    if (internal_node) {
        internal_node->stop();
    }

    if (network_thread.joinable()) {
        network_thread.join();
    }

    if (tui_thread.joinable()) {
        tui_thread.join();
    }

    internal_node.reset();
}
