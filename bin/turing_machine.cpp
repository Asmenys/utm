#include "turing_machine.hpp"
#include <fstream>
#include <iostream>
#include <string>
TuringMachine::TuringMachine(std::string filename) {}

bool TuringMachine::tape_exists(std::string filename) {
  std::ifstream file(filename);
  return file.good();
}

void TuringMachine::open_file(std::string filename) {
  if (!tape_exists(filename)) {
    std::cout << "UTM: tape: I/O error\n";
    return;
  }
  tape_file = std::ifstream(filename);
}
