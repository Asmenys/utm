#include <string>
#include <vector>
class Tape {
public:
  std::vector<std::string> tape;
  int head_position;
  Tape(std::vector<std::string> tape, int head_position);
  Tape(std::vector<std::string>);
  void move_head(std::string direction);
};