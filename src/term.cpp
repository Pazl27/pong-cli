#include <iostream>

#include <term.hpp>

std::ostream& screen = std::cout;

void term::clear() {
    screen << "\33[2J";
}

void term::move_cursor(size_t x, size_t y) {
    screen << "\033[" << y << ";" << x << "H";
}

void term::hide_cursor() {
    screen << "\033[?25l";
}

void term::show_cursor() {
    screen << "\033[?25h";
}

void term::render() {
    screen.flush();
}

void term::draw(std::string c) {
    screen << c;
}

void term::reset() {
  term::clear();
  term::show_cursor();
  term::move_cursor(0, 0);
}

std::string term::color(Color c, std::string s) {
  switch (c) {
    case Color::GREEN:
      return "\033[1;32m" + s + "\033[0m";
    case Color::RED:
      return "\033[1;31m" + s + "\033[0m";
    default:
      return s;
  }
}
