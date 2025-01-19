#ifndef PADDLE_HPP
#define PADDLE_HPP

class Paddle {
   public:
   Paddle(int x, int y);
   void move_up();
   void move_down(int max_y);
   void draw() const;

   int get_y() const { return y; }
    int get_x() const { return x; }

    private:
    int x;
    int y;
};

#endif
