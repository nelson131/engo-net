#include "console.hpp"

Console::Console(const Rect& rect)
    : rect(rect), message_list(rect.get_size().y - 3) {}

void Console::draw(Buffer& buf) {
    rect.draw(buf);
    size_t x = rect.get_vec().x + 2, y = rect.get_vec().y + 1;

    std::span<Message> span = message_list.get_span();

    for (const auto& message : span) {
        buf.put(engo::Pair<size_t, size_t>{x, y++},
                message.author + ": " + message.content);
    }

    buf.put(engo::Pair<size_t, size_t>(x, y), "> " + text_input.get_current());
}

void Console::sumbit_input() {
    message_list.add(
        {"admin", text_input.get_current(), std::chrono::system_clock::now()});

    text_input.clear();
    message_list.scroll_down();
}

const Rect& Console::get_rect() const noexcept { return rect; }

void Console::change_rect(const Rect& rect) noexcept { this->rect = rect; }

MessageList& Console::get_message_list() { return message_list; }

TextInput& Console::get_input() { return text_input; }
