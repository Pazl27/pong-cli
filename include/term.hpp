#ifndef TERM_HPP_
#define TERM_HPP_

#include <cstddef>

namespace term {


    void clear();

    void move_cursor(size_t x, size_t y);

    void hide_cursor();

    void show_cursor();

    void render();

    void draw(char c);
}

#endif
