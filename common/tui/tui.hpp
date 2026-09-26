#pragma once

#include "../config.hpp"
#include "buffer.hpp"

class TUI {
   public:
    TUI(const engo::Pair<size_t, size_t>& screen_meta, Config& config);

    virtual void render();

    const std::string& get_sep() const noexcept;

    int get_state() const noexcept;

   protected:
    Buffer buf;

   protected:
    virtual void draw_state();
    virtual void make_header();

   private:
    Config& config;

    int state;

    std::string sep;
};
