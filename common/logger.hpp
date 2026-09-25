#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <vector>

class Logger {
   public:
    enum Type { DEBUG, SUCCESS, INFO, WARNING, ERROR };

   public:
    Logger(const std::string& path);
    ~Logger();

    template <typename... targs>
    void log(Type type, const targs&... args) {
        std::lock_guard lock(mutex);

        std::ostringstream ss;
        (ss << ... << args);

        const auto now = std::chrono::system_clock::now();
        const auto time = std::chrono::system_clock::to_time_t(now);

        std::tm tm{};
        localtime_r(&time, &tm);

        file << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " ["
             << type_msgs[type] << "] -> " << ss.str() << "\n";
        file.flush();
    }

   private:
    std::ofstream file;
    std::mutex    mutex;

    std::vector<std::string> type_msgs;
};
