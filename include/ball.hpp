#ifndef BALL_HPP
#define BALL_HPP

#include "paddle.hpp"
#include "direction.hpp"

class Ball {
    public:
    Ball(int x, int y);
    void move();
    void draw() const;
    void check_wall_collision(int max_y);
    bool check_paddle_collision(const Paddle& player);

    int get_x() const { return x; }
    int get_y() const { return y; }
    Direction get_direction() const { return direction; }


    private:
    int x;
    int y;
    Direction direction;

};

#endif
