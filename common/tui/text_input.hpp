#pragma once

#include <cstdint>
#include <string>

class TextInput {
   public:
    TextInput();

    void put(char32_t c);
    void backspace();

    void clear();

    const std::string& get_current() const noexcept;

   private:
    std::string input;
};
