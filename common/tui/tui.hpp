#pragma once

#include <mutex>
#include <queue>

#include "../config.hpp"
#include "buffer.hpp"
#include "console.hpp"
#include "input_handler.hpp"

class TUI {
   public:
    TUI(const engo::Pair<size_t, size_t>& screen_meta);
    ~TUI();

    virtual void run();

    void add_log(const std::string& type, const std::string& message);

    const std::string& get_sep() const noexcept;

   protected:
    Buffer buf;

   protected:
    virtual void render();
    virtual void handle_input();

    void make_header(const std::string& title);
    void handle_console_input(Console& console, int key);

    void process_logs(Console& console, const std::string& author);

   private:
    std::mutex              log_mutex;
    std::queue<std::string> log_queue;

    std::string sep;
};
