#include "console.hpp"

Console::Console(const Rect& rect)
    : rect(rect), message_list(rect.get_size().y - 4) {}

void Console::draw(Buffer& buf) {
    rect.draw(buf);
    size_t x = rect.get_vec().x + 2, y = rect.get_vec().y + 1;

    std::span<Message> span = message_list.get_span();

    for (const auto& message : span) {
        std::string              msg = message.author + ": " + message.content;
        std::vector<std::string> lines = buf.wrap(msg, rect.get_size().x - 3);

        for (const auto& line : lines) {
            buf.put({x, y++}, line);
        }
    }

    buf.put(engo::Pair<size_t, size_t>(x, y), "> " + text_input.get_current());
}

std::string Console::sumbit_input() {
    std::string input = text_input.get_current();
    if (input.empty()) return {};

    message_list.add(
        {"admin", text_input.get_current(), std::chrono::system_clock::now()});

    text_input.clear();

    return input;
}

const Rect& Console::get_rect() const noexcept { return rect; }

void Console::change_rect(const Rect& rect) noexcept { this->rect = rect; }

MessageList& Console::get_message_list() { return message_list; }

TextInput& Console::get_input() { return text_input; }
