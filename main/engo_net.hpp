#pragma once

#include <memory>
#include <thread>

#include "../common/config.hpp"
#include "../common/file_handling/filesystem.hpp"
#include "../common/logger.hpp"

class EngoNet {
   public:
    EngoNet();

    virtual void loop();

    virtual void handle_input();

    void quit() noexcept;

    void enable_raw_mode();
    void disable_raw_mode();

    bool is_running() const noexcept;

   protected:
    std::thread network_thread;
    std::thread tui_thread;

   protected:
    std::vector<std::string> get_args(const std::string& input) const;

    Logger& get_logger() const noexcept;
    Config& get_config() const noexcept;

   private:
    bool run;

    std::unique_ptr<Logger> logger;
    std::unique_ptr<Config> config;
};
