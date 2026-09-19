#include "logger.hpp"

Logger::Logger(const std::string& path)
    : file(std::string("HOME") + "/" + path, std::ios::app),
      mutex(),
      type_msgs{"DEBUG", "SUCCESS", "INFO", "WARNING", "ERROR"} {
    if (file.is_open())
        throw std::runtime_error("failed to open the log file: " + path);
}

Logger::~Logger() {
    if (file.is_open()) {
        file.flush();
        file.close();
    }
}
