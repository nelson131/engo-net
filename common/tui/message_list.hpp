#pragma once

#include <vector>

#include "message.hpp"

class MessageList {
   public:
    MessageList();

    void add(const Message& msg);

    const std::vector<Message>& get_messages() const noexcept;

   private:
    std::vector<Message> messages;
};
