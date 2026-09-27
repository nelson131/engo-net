#include "input_handler.hpp"

#include <fcntl.h>
#include <unistd.h>

InputHandler::InputHandler() { enable_raw_mode(); }

InputHandler::~InputHandler() {
    if (old_flags >= 0) fcntl(STDIN_FILENO, F_SETFL, old_flags);

    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

int InputHandler::pause() {
    char c;
    if (::read(STDIN_FILENO, &c, 1) != 1) return NONE;
    if (c == '\033') return read_escape_sequence();

    return static_cast<unsigned char>(c);
}

int InputHandler::poll() {
    char    c;
    ssize_t n = ::read(STDIN_FILENO, &c, 1);
    if (n != 1) return NONE;
    if (c == '\033') return read_escape_sequence();

    return static_cast<unsigned char>(c);
}

void InputHandler::enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &old_term);

    termios term = old_term;

    term.c_lflag &= ~(ICANON | ECHO);
    term.c_iflag &= ~(IXON | ICRNL);

    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
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
