#include "engo_server.hpp"

EngoServer::EngoServer(size_t wcols, size_t wrows)
    : EngoNet(),
      tui(engo::Pair<size_t, size_t>{wcols, wrows}, state, get_config()) {}

void EngoServer::loop() {
    while (is_running()) {
        tui.render();
    }
}

void EngoServer::stop() {
    if (internal_node) {
        internal_node->stop();
    }

    if (network_thread.joinable()) {
        network_thread.join();
    }

    internal_node.reset();
}
