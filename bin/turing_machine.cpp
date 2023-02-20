#include "turing_machine.hpp"
#include "symbol_node.hpp"
#include "symbol_tree.hpp"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
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

void TuringMachine::read_machine_data() {
  tape_count = get_int();
  for (int i = 0; i < tape_count; i++) {
    tapes.push_back(get_tape());
    tapes[i].head_position = get_int() - 1;
  }
}

bool TuringMachine::new_state() {
  if (tree_map.count(current_state) == 0) {
    std::cout << "UTM: Halted with state " + current_state << std::endl;
    return 0;
  }
  SymbolNode current_state_root = tree_map.at(current_state).root;
  std::string current_symbol = tapes[0].current_symbol();
  if (current_state_root.adjacent_nodes.count(current_symbol) == 0) {
    throw std::runtime_error("UTM: error: Halted. No rule for state " +
                             current_state + " and symbol " + current_symbol +
                             "\n");
  }
  SymbolNode current_symbol_node =
      current_state_root.adjacent_nodes.at(current_symbol);
  SymbolNode new_symbol_node =
      current_symbol_node.adjacent_nodes.begin()->second;
  tapes[0].set_new_symbol(new_symbol_node.value);
  SymbolNode movement_node = new_symbol_node.adjacent_nodes.begin()->second;
  tapes[0].move_head(movement_node.value);
  current_state = movement_node.adjacent_nodes.begin()->first;
  return 1;
}

void TuringMachine::start() {
  read_machine_data();
  build_state_trees();
  while (new_state()) {
    system("clear");
    tapes[0].print_state();
  }
}