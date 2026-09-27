#include "input_handler.hpp"

#include <fcntl.h>
#include <unistd.h>

InputHandler::InputHandler() {}

int InputHandler::pause() {
    char c;
    if (::read(STDIN_FILENO, &c, 1) != 1) return NONE;
    if (c == '\033') return read_escape_sequence();

    return static_cast<unsigned char>(c);
}

int InputHandler::poll() {
    int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (old_flags == -1) return NONE;
    if (fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK) == -1) return NONE;

    int result = pause();

    fcntl(STDIN_FILENO, F_SETFL, old_flags);

    return result;
}

int InputHandler::read_escape_sequence() {
    char seq[2];
    if (::read(STDIN_FILENO, &seq[0], 1) != 1) return ESC;
    if (::read(STDIN_FILENO, &seq[1], 1) != 1) return ESC;
    if (seq[0] != '[') return ESC;
    switch (seq[1]) {
        case 'A':
            return ARROW_UP;
        case 'B':
            return ARROW_DOWN;
        case 'C':
            return ARROW_RIGHT;
        case 'D':
            return ARROW_LEFT;
        default:
            return ESC;
    }
}
