#ifndef BOT_HPP
#define BOT_HPP

#include "ball.hpp"

class Bot {
    public:
    Bot(int x, int y);
    void move_up();
    void move_down(int max_y);
    void draw() const;
    void calc_next_move(const Ball &ball);

    int get_y() const { return y; }
    int get_x() const { return x; }

    private:
    int x;
    int y;

};

#endif
