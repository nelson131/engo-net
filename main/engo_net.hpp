#pragma once

#include <memory>

#include "../common/config.hpp"
#include "../common/file_handling/filesystem.hpp"
#include "../common/logger.hpp"

class EngoNet {
   public:
    EngoNet();

    virtual void loop();

    void quit() noexcept;

    bool is_running() const noexcept;

   protected:
    std::vector<std::string> get_args(const std::string& input) const;

    Logger& get_logger() const noexcept;
    Config& get_config() const noexcept;

   private:
    bool run;

    std::unique_ptr<Logger> logger;
    std::unique_ptr<Config> config;
};
