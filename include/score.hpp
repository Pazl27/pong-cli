#ifndef SCORE_HPP
#define SCORE_HPP

class Score {
    public:
    Score();
    void increment_player_score();
    void increment_bot_score();
    void draw(const int width) const;

    private:
    int player_score;
    int bot_score;
};

#endif
