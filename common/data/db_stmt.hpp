#pragma once

#include <sqlite3.h>

#include <iostream>

class DB_stmt {
   public:
    DB_stmt(sqlite3_stmt* stmt = nullptr);
    ~DB_stmt();

    sqlite3_stmt*& get() noexcept;

    template <typename T>
    void bind(size_t idx, T value) {
        if constexpr (std::is_same_v<T, int> || std::is_same_v<T, size_t>) {
            sqlite3_bind_int(raw, idx, value);
        } else if constexpr (std::is_same_v<T, std::string>) {
            sqlite3_bind_text(raw, idx, value.c_str(), -1, SQLITE_TRANSIENT);
        } else if constexpr (std::is_same_v<T, time_t>) {
            sqlite3_bind_int64(raw, idx, value);
        }
    }

   private:
    sqlite3_stmt* raw;
};
