#pragma once

#include <termios.h>

class InputHandler {
   public:
    enum Key {
        NONE = -1,
        ESC = 27,
        ARROW_UP = 1000,
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT
    };

   public:
    InputHandler();
    ~InputHandler();

    int pause();
    int poll();

   private:
    termios old_term{};
    int     old_flags = -1;

    void enable_raw_mode();

    int read_escape_sequence();
};
