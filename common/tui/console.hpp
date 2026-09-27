#pragma once

#include "buffer.hpp"
#include "message_list.hpp"
#include "rect.hpp"
#include "text_input.hpp"

class Console {
   public:
    Console(const Rect& rect);

    void draw(Buffer& buf);
    void sumbit_input();

    const Rect& get_rect() const noexcept;
    void        change_rect(const Rect& rect) noexcept;

    MessageList& get_message_list();
    TextInput&   get_input();

   private:
    Rect rect;

    MessageList message_list;
    TextInput   text_input;
};
