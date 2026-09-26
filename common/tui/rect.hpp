#pragma once

#include <iostream>

#include "../utils/pair.hpp"
#include "buffer.hpp"

class Rect {
   public:
    Rect(size_t x, size_t y, size_t w, size_t h);
    Rect(const engo::Pair<size_t, size_t>& vec,
         const engo::Pair<size_t, size_t>& size);

    void draw(Buffer& buf);

    void center(size_t w, size_t h);
    void center_x(size_t w);
    void center_y(size_t h);

    const engo::Pair<size_t, size_t>& get_vec() const noexcept;
    const engo::Pair<size_t, size_t>& get_size() const noexcept;

   private:
    engo::Pair<size_t, size_t> vec;
    engo::Pair<size_t, size_t> size;
};
