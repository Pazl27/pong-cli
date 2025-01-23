#ifndef TERM_HPP_
#define TERM_HPP_

#include <cstddef>
#include <string>

enum class Color { GREEN, RED };

namespace term {

void clear();

void move_cursor(size_t x, size_t y);

void hide_cursor();

void show_cursor();

void render();

void draw(std::string c);

void reset();

std::string color(Color c, std::string s);
}

#endif
