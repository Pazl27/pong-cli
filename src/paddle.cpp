#include "paddle.hpp"
#include "term.hpp"

Paddle::Paddle(int x, int y) : x(x), y(y) {}

void Paddle::move_up() {
  if (y > 1)
    y--;
}

void Paddle::move_down(int max_y) {
  if (y <= max_y - 5) {
    y++;
  }
}

void Paddle::draw() const {
  for (int i = 0; i < 7; ++i) {
    term::move_cursor(x, y + i);
    term::draw('|');
  }
}
