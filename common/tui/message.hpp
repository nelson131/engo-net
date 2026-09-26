#pragma once

#include <chrono>
#include <string>

struct Message {
    std::string author;
    std::string content;

    std::chrono::system_clock::time_point time;
};
