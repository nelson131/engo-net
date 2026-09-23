#pragma once

#include <memory>

#include "../common/config.hpp"
#include "../common/file_handling/filesystem.hpp"
#include "../common/logger.hpp"

class EngoNet {
   public:
    EngoNet();

    virtual void loop();

    bool is_running() const noexcept;

   private:
    bool run;

    std::unique_ptr<Logger> logger;
    std::unique_ptr<Config> config;
};
