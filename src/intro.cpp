#include "intro.hpp"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "input.hpp"
#include "term.hpp"

Intro::Intro(int width) {
  this->width = width;
  this->display = true;
  this->read_file("../resources/logo.txt");
}

Intro::~Intro() { term::reset(); }

void Intro::read_file(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  }

  std::string line;
  while (std::getline(file, line)) {
    this->logo.push_back(line);
  }

  file.close();
}

void Intro::draw() const {
  term::clear();
  uint length = this->logo.front().size();
  for (int i = 0; i < this->logo.size(); i++) {
    term::move_cursor((this->width / 2) - (length / 2), 10 + i);
    term::draw(term::color(Color::GREEN,this->logo[i]));
  }
  const std::string message = "Press " + term::color(Color::RED, "SPACE") + " to start";
  length = std::string("Press SPACE to start").size();
  term::move_cursor((this->width / 2) - (length / 2), 20);
  term::draw(message);
  term::render();
}

void Intro::get_input() {
  while (this->display) {
    if (input::kbhit()) {
      input::Key key = input::getch();
      if (key == input::Key::SPACE) {
        this->display = false;
      } else if (key == input::Key::EXIT) {
        term::reset();
        std::exit(0);
      }
    }
  }
}
