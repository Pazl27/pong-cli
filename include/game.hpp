#ifndef GAME_HPP
#define GAME_HPP

#include <paddle.hpp>
#include <bot.hpp>
#include <ball.hpp>
#include <score.hpp>
#include <sys/types.h>

class Game {
    public:
        Game();
        ~Game();
        void run();

    private:
    int width, height;
    Paddle player;
    Bot bot;
    Ball ball;
    Score score;

    uint move_counter;
    const int move_threshold;

    void get_terminal_size(int &width, int &height);
};

#endif
