#include "turing_machine.hpp"
#include "symbol_node.hpp"
#include "symbol_tree.hpp"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
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

void TuringMachine::get_tapes() {
  for (int i = 0; i < tape_count; i++) {
    std::vector<std::string> tape;
    std::string tape_from_file;
    tape_file >> tape_from_file;
    for (int i = 0; i < tape_from_file.size(); i++) {
      tape.push_back(std::string(1, tape_from_file[i]));
    }
    tapes.push_back(tape);
  }
}

std::vector<std::string> TuringMachine::get_symbols() {
  std::vector<std::string> symbols;
  for (int i = 0; i < 5; i++) {
    std::string symbol;
    tape_file >> symbol;
    symbols.push_back(symbol);
  }
  return symbols;
}

void TuringMachine::symbols_to_tree(std::vector<std::string> symbols) {
  SymbolTree tree(symbols.front());
  tree_map.insert(std::pair<std::string, SymbolTree>(symbols.front(), tree));
  std::deque<std::string> nodes(symbols.begin() + 1, symbols.end());
  tree_map.at(symbols.front()).insert_branch(nodes);
}

void TuringMachine::read_machine_data() {
  tape_file >> tape_count;
  get_tapes();
  for (int i = 0; i < tape_count; i++) {
    tape_file >> tapes[i].head_position;
  }
}

void TuringMachine::build_state_trees() {
  while (true) {
    if (tape_file.peek() == EOF) {
      break;
    }
    std::vector<std::string> symbols = get_symbols();
    symbols_to_tree(symbols);
  }
}

SymbolNode TuringMachine::get_current_symbol_node(SymbolNode const &root) {
  std::string current_symbol = tapes[0].current_symbol();
  if (root.adjacent_nodes.count(current_symbol) == 0) {
    throw std::runtime_error("UTM: error: Halted. No rule for state " +
                             root.value + " and symbol " + current_symbol +
                             "\n");
  }
  return root.adjacent_nodes.at(current_symbol);
}

bool TuringMachine::new_state() {
  if (tree_map.count(current_state) == 0) {
    std::cout << "UTM: Halted with state " + current_state << std::endl;
    return 0;
  }
  SymbolNode current_state_root = tree_map.at(current_state).root;
  SymbolNode current_symbol_node = get_current_symbol_node(current_state_root);
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
}