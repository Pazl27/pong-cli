#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <term.hpp>
#include <input.hpp>

enum class Direction {
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

struct Paddle {
    int x;
    int y;

    Paddle(int x, int y) : x(x), y(y) {}

    void move_up() {
        if (y > 1)
            y--;
    }

    void move_down(int max_y) {
        if (y <= max_y - 5) {
            y++;
        }
    }

    void draw() const {
        for (int i = 0; i < 7; ++i) {
            term::move_cursor(x, y + i);
            term::draw('|');
        }
    }
};

struct Ball {
    int x;
    int y;
    Direction direction;

    Ball(int x, int y) : x(x), y(y) {
        direction = Direction::UP_LEFT;
    }

    void move() {
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

    void draw() const {
        term::move_cursor(x, y);
        term::draw('O');
    }

    void check_wall_collision(int max_y) {
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

    bool check_paddle_collision(const Paddle& player) {
        if (x == player.x + 1) {
            if (y >= player.y && y < player.y + 5) {
                if (direction == Direction::UP_LEFT)
                    direction = Direction::UP_RIGHT;
                else if (direction == Direction::DOWN_LEFT)
                    direction = Direction::DOWN_RIGHT;
                return true;
            }
        }
        return false;
    }
};

struct Bot {
    int x;
    int y;

    Bot(int x, int y) : x(x), y(y) {}

    void move_up() {
        if (y > 1)
            y--;
    }

    void move_down(int max_y) {
        if (y <= max_y - 7) {
            y++;
        }
    }

    void draw() const {
        for (int i = 0; i < 7; ++i) {
            term::move_cursor(x, y + i);
            term::draw('|');
        }
    }

    void calc_next_move(const Ball &ball) {
        if (ball.y < y) {
            move_up();
        } else if (ball.y > y) {
            move_down(30);
        }
    }
};

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
