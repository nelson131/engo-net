#pragma once

#include <memory>
#include <mutex>
#include <queue>

#include "../../server/server_state.hpp"
#include "../logger.hpp"
#include "console.hpp"
#include "rect.hpp"
#include "tui.hpp"

class ServerTUI : public TUI {
   public:
    ServerTUI(const engo::Pair<size_t, size_t>& screen_meta, ServerState& state,
              Config& config, Logger& logger);

    void render() override;

    void write_console(char c);
    void write_console(const std::string& author, const std::string& message);
    void pop_console();
    std::string sumbit_console();

    void add_log(const std::string& type, const std::string& message);

   private:
    ServerState& state;
    Logger&      logger;

    std::unique_ptr<Rect> rect;
    std::string           rect_floor;

    std::unique_ptr<Console> console;

    std::mutex              log_mutex;
    std::queue<std::string> log_queue;

   private:
    void draw_state() override;
    void make_header() override;

    void process_logs();
};
