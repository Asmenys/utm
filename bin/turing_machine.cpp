#include "turing_machine.hpp"
#include "symbol_node.hpp"
#include "symbol_tree.hpp"
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

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

int TuringMachine::get_int() {
  int integer;
  tape_file >> integer;
  return integer;
}

std::vector<std::string>
TuringMachine::string_to_vector(const std::string &string) {
  std::vector<std::string> vector;
  for (auto i = string.begin(); i != string.end(); ++i) {
    vector.emplace_back(i);
  }
  return vector;
}

std::vector<std::string> TuringMachine::get_tape() {
  std::string tape_from_file;
  tape_file >> tape_from_file;
  return string_to_vector(tape_from_file);
}

std::vector<std::string> TuringMachine::get_symbols() {
  std::string symbol_string;
  tape_file >> symbol_string;
  return string_to_vector(symbol_string);
}

void TuringMachine::symbols_to_tree(std::vector<std::string> symbols) {
  SymbolTree tree(symbols.front());
  tree_map.insert(std::pair<std::string, SymbolTree>(symbols.front(), tree));
  std::deque<std::string> nodes(symbols.begin() + 1, symbols.end());
  tree.insert_branch(nodes);
}