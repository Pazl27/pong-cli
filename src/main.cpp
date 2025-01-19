#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <term.hpp>
#include <input.hpp>
#include <paddle.hpp>
#include <bot.hpp>
#include <ball.hpp>
#include <direction.hpp>


void get_terminal_size(int &width, int &height) {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    std::cerr << "Error: Unable to get terminal size" << std::endl;
    exit(1);
  }
  width = w.ws_col;
  height = w.ws_row;
}

int main() {
  int width, height;
  get_terminal_size(width, height);

  Paddle player(3, height / 2 - 3);
  Bot bot(width - 3, height / 2 - 3);
  Ball ball(width / 2, height / 2);

  term::hide_cursor();
  input::set_conio_terminal_mode();

  uint move_counter = 0;
  const int move_threshold = 2;

  while (true) {
    ball.check_wall_collision(height);
    ball.check_paddle_collision(player);

    term::clear();
    term::move_cursor(0, 0);

    player.draw();
    bot.draw();
    ball.draw();
    term::render();

    if (input::kbhit()) {
        input::Key key = input::getch();
        switch(key) {
            case input::Key::UP:
                player.move_up();
                break;
            case input::Key::DOWN:
                player.move_down(height);
                break;
            case input::Key::EXIT:
                goto exit_loop;
            default:
                break;
        }
    }

    if (move_counter >= move_threshold) {
        ball.move();
        bot.calc_next_move(ball);
        move_counter = 0;
    } else {
        move_counter++;
    }

    usleep(30000);
  }

  exit_loop:
  input::reset_terminal_mode();
  term::clear();
  term::show_cursor();
  return 0;
}
