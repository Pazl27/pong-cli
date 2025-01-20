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
