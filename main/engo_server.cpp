#include "engo_server.hpp"

EngoServer::EngoServer(size_t wcols, size_t wrows)
    : EngoNet(),
      tui(engo::Pair<size_t, size_t>{wcols, wrows}, state, get_config()) {
    tui_thread = std::thread([this] {
        using namespace std::chrono_literals;

        while (is_running()) {
            handle_input();
            tui.render();
            std::this_thread::sleep_for(16ms);
        }
    });
}

EngoServer::~EngoServer() { stop(); }

void EngoServer::loop() {
    while (is_running()) {
        // network
    }
}

void EngoServer::handle_input() {
    int key = input_handler.poll();
    if (key == InputHandler::NONE) return;

    if (key == InputHandler::ENTER1 || key == InputHandler::ENTER2) {
        std::string input = tui.sumbit_console();
        execute_cmd(input);
        return;
    }

    if (key == InputHandler::BACKSPACE) {
        tui.pop_console();
        return;
    }

    if (key >= 32 && key <= 126) {
        tui.write_console(key);
        return;
    }
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

void EngoServer::execute_cmd(const std::string& input) {
    Command cmd = command_parser.parse(input);

    switch (cmd.type) {
        case CommandType::EXIT:
            quit();
            break;
        case CommandType::HELP:
            tui.write_console("server", get_help_msg());
            break;
        case CommandType::UNKNOWN:
            break;
        default:
            break;
    }
}

std::string EngoServer::get_help_msg() const noexcept {
    return "exit -> quit from application, help -> send this message";
}
