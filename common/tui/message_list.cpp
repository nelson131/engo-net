#include "message_list.hpp"

MessageList::MessageList() {}

void MessageList::add(const Message& msg) {
    if (msg.content.empty() || msg.author.empty()) return;

    messages.push_back(msg);
}

const std::vector<Message>& MessageList::get_messages() const noexcept {
    return messages;
}
