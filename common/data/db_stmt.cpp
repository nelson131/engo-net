#include "db_stmt.hpp"

DB_stmt::DB_stmt(sqlite3_stmt* stmt) : raw(stmt) {}

DB_stmt::~DB_stmt() {
    if (raw) sqlite3_finalize(raw);
}

sqlite3_stmt*& DB_stmt::get() noexcept { return raw; }
