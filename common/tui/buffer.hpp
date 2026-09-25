#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../utils/pair.hpp"

#define STYLE_NONE 0
#define STYLE_BOLD (1 << 0)
#define STYLE_UNDERLINE (1 << 1)

#define COLOR_DEFAULT -1
#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
#define COLOR_MAGENTA 5
#define COLOR_CYAN 6
#define COLOR_WHITE 7

typedef char32_t c32;
typedef int32_t  i32;
typedef uint8_t  u8;
typedef uint32_t u32;

struct Cell {
    c32 c;
    i32 tg;
    i32 bg;
    u8  fl;

    const bool operator==(const Cell& other) const {
        return c == other.c && tg == other.tg && bg == other.bg &&
               fl == other.fl;
    }
};

class Buffer {
   public:
    Buffer(size_t window_cols, size_t window_rows);

    void clear();

    void put(engo::Pair<size_t, size_t> v, c32 c, i32 tg, i32 bg, u8 fl);
    void put(engo::Pair<size_t, size_t> v, std::string_view text, i32 tg,
             i32 bg, u8 fl);

    void render();

    Cell& get_cell(engo::Pair<size_t, size_t> pos);

   private:
    size_t window_cols;
    size_t window_rows;
    size_t size;

    std::vector<Cell> actual;
    std::vector<Cell> old;

   private:
    size_t to_index(engo::Pair<size_t, size_t> v) const;

    void cell_reset(Cell& cell);
    void cell_cmpl(Cell& cell, i32& c_tg, i32& c_bg, u8& c_fl);

    bool   utf8_decode(std::string_view str, size_t& offset, c32& c) const;
    void   utf8_encode(c32 c, std::string& output) const;
    size_t codepoint_width(c32 c) const;

    void render_cell(const Cell& cell);
};
