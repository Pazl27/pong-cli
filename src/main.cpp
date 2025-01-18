#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <term.hpp>

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

    void draw() {
        for (int i = 0; i < 5; ++i) {
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

    void draw() {
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

void get_terminal_size(int &width, int &height) {
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
    std::cerr << "Error: Unable to get terminal size" << std::endl;
    exit(1);
  }
  width = w.ws_col;
  height = w.ws_row;
}

char get_input() {
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

int main() {
  int width, height;
  get_terminal_size(width, height);

  Paddle player(3, height / 2 - 2);
  Ball ball(width / 2, height / 2);

  term::hide_cursor();

  while (true) {
    ball.move();
    ball.check_wall_collision(height);
    ball.check_paddle_collision(player);

    term::clear();
    term::move_cursor(0, 0);

    player.draw();
    ball.draw();
    term::render();

    char input = get_input();

    if (input == 'k') {
      player.move_up();
    } else if (input == 'j') {
      player.move_down(height);
    } else if (input == 'q') {
      break;
    }

    usleep(10000);
  }

  term::show_cursor();
  return 0;
}
