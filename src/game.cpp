#include "game.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <ball.hpp>
#include <bot.hpp>
#include <direction.hpp>
#include <input.hpp>
#include <paddle.hpp>
#include <term.hpp>
#include <score.hpp>

Game::Game()
    : player(3, height / 2 - 3, 7), bot(width - 3, height / 2 - 3, 7),
      ball(width / 2, height / 2), move_counter(0), move_threshold(2),
      score() {
  get_terminal_size(width, height);

  player = Paddle(3, height / 2 - 3, 7);
  bot = Bot(width - 3, height / 2 - 3, 7);
  ball = Ball(width / 2, height / 2);
  score = Score();

  term::hide_cursor();
  input::set_conio_terminal_mode();
}

void Game::get_terminal_size(int &width, int &height) {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    std::cerr << "Error: Unable to get terminal size" << std::endl;
    exit(1);
  }
  width = w.ws_col;
  height = w.ws_row;
}

Game::~Game() {
  input::reset_terminal_mode();
  term::clear();
  term::show_cursor();
}

void Game::run() {
  bool running = true;
  while (running) {

    ball.check_wall_collision(height);
    ball.check_paddle_collision(player);
    ball.check_bot_collision(bot);
    ball.check_goal(score, width, height);

    term::clear();
    term::move_cursor(0, 0);

    for (int i = 1; i < height; i++) {
      term::move_cursor(width / 2, i);
      term::draw("|");
    }

    player.draw();
    bot.draw();
    ball.draw();
    score.draw(width);
    term::render();

    if (input::kbhit()) {
      input::Key key = input::getch();
      switch (key) {
      case input::Key::UP:
        player.move_up();
        break;
      case input::Key::DOWN:
        player.move_down(height);
        break;
      case input::Key::EXIT:
        running = false;
        break;
      default:
        break;
      }
    }

    if (move_counter >= move_threshold) {
      ball.move();
      bot.calc_next_move(ball, height);
      move_counter = 0;
    } else {
      move_counter++;
    }

    usleep(30000);
  }
}
