#include "turing_machine.hpp"
#include "symbol_node.hpp"
#include "symbol_tree.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

TuringMachine::TuringMachine(std::string filename) : current_state("0") {
  open_file(filename);
}

bool TuringMachine::tape_exists(std::string filename) {
  std::ifstream file(filename);
  return file.good();
}

void TuringMachine::open_file(std::string filename) {
  if (!tape_exists(filename)) {
    throw std::runtime_error("UTM: tape: I/O error\n");
    return;
  }
  tape_file = std::ifstream(filename);
}

int TuringMachine::get_int() {
  int integer;
  tape_file >> integer;
  return integer;
}

std::vector<std::string> TuringMachine::get_tape() {
  std::vector<std::string> vector;
  std::string tape_from_file;
  tape_file >> tape_from_file;
  for (int i = 0; i < tape_from_file.size(); i++) {
    vector.push_back(std::string(1, tape_from_file[i]));
  }
  return vector;
}

std::vector<std::string> TuringMachine::get_symbols() {
  std::vector<std::string> symbols;
  while (tape_file.peek() != '\n') {
    std::string symbol;
    tape_file >> symbol;
    symbols.push_back(symbol);
  }
  tape_file.get();
  if (symbols.size() != 5) {
    throw std::runtime_error(
        "UTM: tape: instructions: invalid argument count\n");
  }
  return symbols;
}

void TuringMachine::symbols_to_tree(std::vector<std::string> symbols) {
  SymbolTree tree(symbols.front());
  tree_map.insert(std::pair<std::string, SymbolTree>(symbols.front(), tree));
  std::deque<std::string> nodes(symbols.begin() + 1, symbols.end());
  tree_map.at(symbols.front()).insert_branch(nodes);
}

void TuringMachine::build_state_trees() {
  tape_file >> std::ws;
  while (true) {
    if (tape_file.peek() == EOF) {
      break;
    }
    std::vector<std::string> symbols = get_symbols();
    symbols_to_tree(symbols);
  }
}

void TuringMachine::start() {
  tape_count = get_int();
  for (int i = 0; i < tape_count; i++) {
    tapes.push_back(get_tape());
    tapes[i].head_position = get_int();
  }
  build_state_trees();
}