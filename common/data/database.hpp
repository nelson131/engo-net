#pragma once

#include <memory>

#include "../file_handling/filesystem.hpp"
#include "db_stmt.hpp"

class Database {
   public:
    Database();
    ~Database();

    bool                     execute(const std::string& query);
    std::unique_ptr<DB_stmt> prepare(const std::string& query);

   private:
    sqlite3* src;
};
