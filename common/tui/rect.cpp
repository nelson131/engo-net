#include "rect.hpp"

Rect::Rect(size_t x, size_t y, size_t w, size_t h) : vec{x, y}, size{w, h} {}

Rect::Rect(const engo::Pair<size_t, size_t>& vec,
           const engo::Pair<size_t, size_t>& size)
    : vec(vec), size(size) {}

void Rect::draw(Buffer& buf) {
    std::string line = std::string(size.x, '-');
    line[0] = '+';
    line[size.x - 1] = '+';

    buf.put(vec, line);
    buf.put(engo::Pair<size_t, size_t>{vec.x, vec.y + size.y - 1}, line);

    line = std::string(size.y - 2, '|');

    buf.putv(engo::Pair<size_t, size_t>{vec.x, vec.y + 1}, line);
    buf.putv(engo::Pair<size_t, size_t>{vec.x + size.x - 1, vec.y + 1}, line);
}

void Rect::center(size_t w, size_t h) {
    center_x(w);
    center_y(h);
}

void Rect::center_x(size_t w) {
    if (w > size.x) {
        vec.x = (w - size.x) / 2;
    }
}

void Rect::center_y(size_t h) {
    if (h > size.y) {
        vec.y = (h - size.y) / 2;
    }
}

const engo::Pair<size_t, size_t>& Rect::get_vec() const noexcept { return vec; }

const engo::Pair<size_t, size_t>& Rect::get_size() const noexcept {
    return size;
}
