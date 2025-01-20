
#include "ball.hpp"
#include "direction.hpp"
#include "paddle.hpp"
#include "bot.hpp"
#include "term.hpp"
#include "score.hpp"

Ball::Ball(int x, int y) : x(x), y(y) { direction = Direction::UP_LEFT; }

void Ball::move() {
  switch (direction) {
  case Direction::UP_LEFT:
    x -= 2;
    y -= 1;
    break;
  case Direction::UP_RIGHT:
    x += 2;
    y -= 1;
    break;
  case Direction::DOWN_LEFT:
    x -= 2;
    y += 1;
    break;
  case Direction::DOWN_RIGHT:
    x += 2;
    y += 1;
    break;
  }
}

void Ball::draw() const {
  term::move_cursor(x, y);
  term::draw("O");
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
  if (x <= player.get_x() + 1 && x >= player.get_x() - 1) {
    if (y >= player.get_y() && y < player.get_y() + 7) {
      if (direction == Direction::UP_LEFT)
        direction = Direction::UP_RIGHT;
      else if (direction == Direction::DOWN_LEFT)
        direction = Direction::DOWN_RIGHT;
      return true;
    }
  }
  return false;
}

bool Ball::check_bot_collision(const Bot &bot) {
  if (x >= bot.get_x() - 1 && x <= bot.get_x() + 1) {
    if (y >= bot.get_y() && y < bot.get_y() + 7) {
      if (direction == Direction::UP_RIGHT)
        direction = Direction::UP_LEFT;
      else if (direction == Direction::DOWN_RIGHT)
        direction = Direction::DOWN_LEFT;
      return true;
    }
  }
  return false;
}

void Ball::reset(Direction direction, int width, int height) {
  x = width / 2;
  y = height / 2;
  this->direction = direction;
}

void Ball::check_goal(Score &score, int width, int height) {
  if (x <= 1) {
    score.increment_player_score();
    reset(Direction::UP_RIGHT, width, height);
  }
  if (x >= width - 1) {
    score.increment_bot_score();
    reset(Direction::DOWN_LEFT, width, height);
  }
}
