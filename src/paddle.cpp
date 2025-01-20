#include "paddle.hpp"
#include "term.hpp"

Paddle::Paddle(int x, int y, int size) : x(x), y(y), size(size) {}

void Paddle::move_up() {
  if (y > 1)
    y--;
}

void Paddle::move_down(int max_y) {
  if (y <= max_y - this->size) {
    y++;
  }
}

void Paddle::draw() const {
  for (int i = 0; i < this->size; ++i) {
    term::move_cursor(x, y + i);
    term::draw("|");
  }
}
