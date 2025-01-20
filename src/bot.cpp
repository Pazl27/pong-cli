#include "bot.hpp"
#include "ball.hpp"
#include "term.hpp"

Bot::Bot(int x, int y, int size) : x(x), y(y) {}

void Bot::move_up() {
  if (y > 1)
    y--;
}

void Bot::move_down(int max_y) {
  if (y <= max_y - this->size) {
    y++;
  }
}

void Bot::draw() const {
  for (int i = 0; i < this->size; ++i) {
    term::move_cursor(x, y + i);
    term::draw("|");
  }
}

void Bot::calc_next_move(const Ball &ball, int max_y) {
  if (ball.get_y() - this->size / 2 < y) {
    move_up();
  } else if (ball.get_y() - this->size / 2 > y) {
    move_down(max_y);
  }
}
