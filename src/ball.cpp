#include "ball.hpp"
#include "direction.hpp"
#include "paddle.hpp"
#include "term.hpp"

Ball::Ball(int x, int y) : x(x), y(y) { direction = Direction::UP_LEFT; }

void Ball::move() {
  switch (direction) {
  case Direction::UP_LEFT:
    x--;
    y--;
    break;
  case Direction::UP_RIGHT:
    x++;
    y--;
    break;
  case Direction::DOWN_LEFT:
    x--;
    y++;
    break;
  case Direction::DOWN_RIGHT:
    x++;
    y++;
    break;
  }
}

void Ball::draw() const {
  term::move_cursor(x, y);
  term::draw('O');
}

void Ball::check_wall_collision(int max_y) {
  if (y <= 1) {
    if (direction == Direction::UP_LEFT)
      direction = Direction::DOWN_LEFT;
    else if (direction == Direction::UP_RIGHT)
      direction = Direction::DOWN_RIGHT;
  }
  if (y >= max_y - 1) {
    if (direction == Direction::DOWN_LEFT)
      direction = Direction::UP_LEFT;
    else if (direction == Direction::DOWN_RIGHT)
      direction = Direction::UP_RIGHT;
  }
}

bool Ball::check_paddle_collision(const Paddle &player) {
  if (x == player.get_x() + 1) {
    if (y >= player.get_y() && y < player.get_y() + 5) {
      if (direction == Direction::UP_LEFT)
        direction = Direction::UP_RIGHT;
      else if (direction == Direction::DOWN_LEFT)
        direction = Direction::DOWN_RIGHT;
      return true;
    }
  }
  return false;
}
