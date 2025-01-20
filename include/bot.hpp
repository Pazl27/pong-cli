#ifndef BOT_HPP
#define BOT_HPP

class Ball;

class Bot {
    public:
    Bot(int x, int y, int size);
    void move_up();
    void move_down(int max_y);
    void draw() const;
    void calc_next_move(const Ball &ball, int max_y);

    int get_y() const { return y; }
    int get_x() const { return x; }

    private:
    int x;
    int y;
    int size;

};

#endif
