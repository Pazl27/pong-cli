#ifndef TERM_HPP_
#define TERM_HPP_

#include <iostream>

namespace term {

    std::ostream& screen = std::cout;

    void clear() {
        screen << "\33[2J";
    }

    void move_cursor(size_t x, size_t y) {
        screen << "\033[" << y << ";" << x << "H";
    }

    void hide_cursor() {
        screen << "\033[?25l";
    }

    void show_cursor() {
        screen << "\033[?25h";
    }

    void render() {
        screen.flush();
    }

    void draw(char c) {
        screen << c;
    }
}

#endif
