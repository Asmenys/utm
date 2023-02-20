#include "turing_machine.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
TuringMachine::TuringMachine(std::string filename) { open_file(filename); }

bool TuringMachine::tape_exists(std::string filename) {
  std::ifstream file(filename);
  return file.good();
}

void TuringMachine::open_file(std::string filename) {
  if (!tape_exists(filename)) {
    throw std::runtime_error("UTM: tape: I/O error");
    return;
  }
  tape_file = std::ifstream(filename);
}
