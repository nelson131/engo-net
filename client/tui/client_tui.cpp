#include "client_tui.hpp"

ClientTUI::ClientTUI(const engo::Pair<size_t, size_t>& screen_meta,
                     CommandCallback cmd_callback, Logger& logger)
    : TUI(screen_meta),
      screen_meta(screen_meta),
      cmd_callback(std::move(cmd_callback)),
      logger(logger),
      focus_state(GENERAL_CHATS) {
    buf.clear();

    size_t rect_w = (size_t)screen_meta.x * 0.25;
    chats_rect = std::make_unique<Rect>(
        engo::Pair<size_t, size_t>{0, 3},
        engo::Pair<size_t, size_t>{rect_w, screen_meta.y - 6});

    rect_floor = std::string(rect_w - 2, '-');
}

void ClientTUI::run() {
    handle_input();
    render();
}

void ClientTUI::send_help_msg() {
    std::string msg =
        "exit -> quit from application, help -> send this message, stop -> "
        "stop the network side";

    console->get_message_list().add("engo-net", msg);
}

void ClientTUI::handle_network_msgs(const std::string& msg) {
    size_t pos = msg.find(":");
    if (pos == std::string::npos) return;

    std::string author = msg.substr(0, pos);
    std::string frmsg = msg.substr(pos + 1);

    console->get_message_list().add(author, frmsg);
}

void ClientTUI::render() {
    buf.clear();
    make_header(CONFIG_ENGO_NAME + std::string(" ") + CONFIG_ENGO_VERSION +
                std::string(" -> client TUI"));
    make_chats_section();
    if (console) process_logs(*console, "engo-net");

    switch (focus_state) {
        case GENERAL_CHATS:
            break;
        case ENGO_CHAT:
            if (console) console->draw(buf);
            break;
        case MESSAGES:
            break;
        default:
            break;
    }

    buf.render();
}

void ClientTUI::handle_input() {
    int key = input_handler.poll();
    if (key == InputHandler::NONE) return;

    switch (focus_state) {
        case GENERAL_CHATS:
            if (key == InputHandler::ESC) {
                focus_state = ENGO_CHAT;
                if (!console) {
                    console = std::make_unique<Console>(
                        "user",
                        Rect{{chats_rect->get_vec().x +
                                  chats_rect->get_size().x + 1,
                              chats_rect->get_vec().y},
                             {screen_meta.x - chats_rect->get_size().x - 1,
                              screen_meta.y - 6}});
                }
                break;
            }
            break;
        case ENGO_CHAT:
            if (console) {
                if (key == InputHandler::ENTER1 ||
                    key == InputHandler::ENTER2) {
                    std::string cmd = console->sumbit_input();
                    if (cmd_callback) {
                        cmd_callback(cmd);
                    }
                    break;
                }

                handle_console_input(*console, key);
            }
            break;
        case MESSAGES:
            if (key == InputHandler::ESC) {
                focus_state = GENERAL_CHATS;
                break;
            }
            break;
        default:
            break;
    }
}

void ClientTUI::make_chats_section() {
    chats_rect->draw(buf);

    size_t x = chats_rect->get_vec().x + 1;
    size_t y = chats_rect->get_vec().y + 1;
    if (focus_state == ENGO_CHAT) {
        buf.put({x, y++}, "engo-net =>", COLOR_BLUE, COLOR_DEFAULT, STYLE_BOLD);
        buf.put({x, y++}, "  #network", COLOR_WHITE, COLOR_DEFAULT, STYLE_BOLD);
    } else {
        buf.put({x, y++}, "engo-net =>");
        buf.put({x, y++}, "  #network");
    }
    buf.put({x, y++}, rect_floor);
}
