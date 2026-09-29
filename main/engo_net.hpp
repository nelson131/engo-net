#pragma once

#include <memory>
#include <thread>

#include "../common/config.hpp"
#include "../common/file_handling/filesystem.hpp"
#include "../common/logger.hpp"

class EngoNet {
   public:
    EngoNet();

    void quit() noexcept;

    bool is_running() const noexcept;

   protected:
    std::thread network_thread;
    std::thread tui_thread;

   protected:
    virtual void stop_overall();
    virtual void stop_network();

    Logger& get_logger() const noexcept;
    Config& get_config() const noexcept;

   private:
    bool run;

    std::unique_ptr<Logger> logger;
    std::unique_ptr<Config> config;
};
