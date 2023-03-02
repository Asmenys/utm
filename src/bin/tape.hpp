#include <iostream>
#include <string>
#include <vector>
class Tape {
public:
  std::vector<std::string> tape;
  int head_position;
  Tape(std::vector<std::string> tape, int head_position);
  Tape(std::vector<std::string>);
  void move_head(std::string direction);
  void after_head_move();
  bool compare_symbol(std::string symbol);
  void set_new_symbol(std::string new_symbol);
  std::string current_symbol();
  void print_state();
};