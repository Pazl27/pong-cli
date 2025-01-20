#include "score.hpp"
#include "term.hpp"

Score::Score() : player_score(0), bot_score(0) {}

void Score::increment_player_score() { player_score++; }

void Score::increment_bot_score() { bot_score++; }

void Score::draw(const int width) const {
  term::move_cursor(width / 2 - 2, 0);
  term::draw(std::to_string(player_score));
  term::move_cursor(width / 2 + 2, 0);
  term::draw(std::to_string(bot_score));
}
