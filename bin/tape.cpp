#include "tape.hpp"
#include "stdexcept"
#include <string>
#include <vector>
Tape::Tape(std::vector<std::string> tape, int head_pos)
    : tape(tape), head_position(head_pos) {}

Tape::Tape(std::vector<std::string> tape) : tape(tape), head_position(0) {}

void Tape::move_head(std::string direction) {
  if (direction != "R" || direction != "L") {
    throw std::runtime_error(
        "UTM: error: tape: invalid direction. Expected R or L got " +
        direction);
  }
  if (direction == "R") {
    head_position++;
  }
  if (direction == "L") {
    head_position--;
  }
  after_head_move();
}

void Tape::after_head_move() {
  if (head_position > tape.size()) {
    tape.push_back(" ");
  }
  if (head_position < 0) {
    head_position = 0;
    tape.insert(tape.begin(), " ");
  }
}

bool Tape::compare_symbol(std::string symbol) {
  return tape.at(head_position) == symbol;
}

void Tape::set_new_symbol(std::string new_symbol) {
  tape.at(head_position) = new_symbol;
}