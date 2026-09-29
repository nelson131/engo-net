#pragma once

#include "../config.hpp"
#include "buffer.hpp"

class TUI {
   public:
    TUI(const engo::Pair<size_t, size_t>& screen_meta);
    ~TUI();

    virtual void run();

    const std::string& get_sep() const noexcept;

   protected:
    Buffer buf;

   protected:
    virtual void render();
    virtual void handle_input();

    virtual void make_header();

   private:
    std::string sep;
};
