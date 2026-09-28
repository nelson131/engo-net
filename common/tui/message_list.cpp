#include "message_list.hpp"

MessageList::MessageList(size_t range)
    : range(range), scroll_bottom(0), messages{} {}

void MessageList::add(const Message& msg) {
    if (msg.content.empty() || msg.author.empty()) return;

    messages.push_back(msg);
    scroll_bottom = messages.size() - 1;
}

void MessageList::add(const std::string& author, const std::string& msg) {
    add({author, msg, std::chrono::system_clock::now()});
}

std::span<Message> MessageList::get_span() noexcept {
    if (messages.empty()) return {};

    size_t end = std::min(scroll_bottom + 1, messages.size());
    size_t begin = end > range ? end - range : 0;

    return {messages.data() + begin, end - begin};
}

const std::vector<Message>& MessageList::get_messages() const noexcept {
    return messages;
}

size_t MessageList::get_range() const noexcept { return range; }

size_t MessageList::get_scroll_bottom() const noexcept { return scroll_bottom; }

void MessageList::scroll_up() noexcept {
    if (scroll_bottom - 1 < 0) return;
    if (messages.size() - scroll_bottom <= range) return;

    scroll_bottom--;
}

void MessageList::scroll_down() noexcept {
    if (scroll_bottom + 1 >= messages.size()) return;
    scroll_bottom++;
}
