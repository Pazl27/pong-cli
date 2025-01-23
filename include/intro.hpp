#include <vector>
#include <string>

class Intro {
public:
  Intro(int width);
  ~Intro();
  void read_file(const std::string &filename);
  void draw() const;
  bool get_display() const { return display; }
  void get_input();

private:
  std::vector<std::string> logo;
  bool display;
  int width;
};
