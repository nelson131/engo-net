#pragma once

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

    int pause();
    int poll();

   private:
    int read_escape_sequence();
};
