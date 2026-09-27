#pragma once

#include <span>
#include <vector>

#include "message.hpp"

class MessageList {
   public:
    MessageList(size_t range);

    void add(const Message& msg);

    std::span<Message>          get_span() noexcept;
    const std::vector<Message>& get_messages() const noexcept;

    size_t get_range() const noexcept;
    size_t get_scroll_bottom() const noexcept;

    void scroll_down() noexcept;

   private:
    size_t range;
    size_t scroll_bottom;

    std::vector<Message> messages;
};
