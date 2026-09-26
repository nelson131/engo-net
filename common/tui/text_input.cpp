#include "text_input.hpp"

TextInput::TextInput() : input() {}

void TextInput::put(char32_t c) { input.push_back(c); }

void TextInput::backspace() {
    if (!input.empty()) input.pop_back();
}

void TextInput::clear() {
    if (!input.empty()) {
        input.clear();
    }
}
