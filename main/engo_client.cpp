#include "engo_client.hpp"

#include <iostream>

EngoClient::EngoClient(size_t wcols, size_t wrows)
    : EngoNet(),
      tui(engo::Pair<size_t, size_t>{wcols, wrows}, get_config(),
          get_logger()) {
    tui_thread = std::thread([this] { tui.render(); });
}

EngoClient::~EngoClient() { stop_overall(); }

void EngoClient::stop_overall() {
    stop_network();

    if (tui_thread.joinable()) {
        tui_thread.join();
    }
}

void EngoClient::stop_network() {
    if (user) {
        user->stop();
        user.reset();
    }

    if (network_thread.joinable()) {
        network_thread.join();
    }
}
