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
}