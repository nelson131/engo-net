#pragma once

#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <vector>

class Logger {
   public:
    enum Type { DEBUG, SUCCESS, INFO, WARNING, ERROR };

    using Callback =
        std::function<void(const std::string&, const std::string&)>;

   public:
    Logger(const std::string& path);
    ~Logger();

    // log only in logfile
    template <typename... targs>
    void log(Type type, const targs&... args) {
        std::lock_guard lock(mutex);

        std::ostringstream ss;
        (ss << ... << args);

        write_logfile(type, ss.str());
    }

    // log in logfile and into callback too
    template <typename... targs>
    void tlog(Type type, const targs&... args) {
        std::lock_guard lock(mutex);

        std::ostringstream ss;
        (ss << ... << args);

        write_logfile(type, ss.str());

        if (callback) callback(type_msgs[type], ss.str());
    }

    void set_callback(Callback callback);

   private:
    std::ofstream file;
    std::mutex    mutex;

    std::vector<std::string> type_msgs;

    Callback callback;

   private:
    void write_logfile(Type type, const std::string& message);
};
