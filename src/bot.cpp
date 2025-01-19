#include "bot.hpp"
#include "term.hpp"
#include "ball.hpp"

    Bot::Bot(int x, int y) : x(x), y(y) {}

    void Bot::move_up() {
        if (y > 1)
            y--;
    }

    void Bot::move_down(int max_y) {
        if (y <= max_y - 7) {
            y++;
        }
    }

    void Bot::draw() const {
        for (int i = 0; i < 7; ++i) {
            term::move_cursor(x, y + i);
            term::draw('|');
        }
    }

    void Bot::calc_next_move(const Ball &ball) {
        if (ball.get_y() < y) {
            move_up();
        } else if (ball.get_y() > y) {
            move_down(30);
        }
    }
