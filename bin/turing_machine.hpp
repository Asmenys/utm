#include "symbol_tree.hpp"
#include "tape.hpp"
#include <fstream>
#include <map>
#include <string>
#include <vector>

class TuringMachine {
  std::string current_state;
  std::map<std::string, SymbolTree> tree_map;
  std::ifstream tape_file;
  int tape_count;
  bool tape_exists(std::string filename);
  void open_file(std::string filename);
  void get_tapes();
  std::string get_symbol_string();
  std::vector<std::string> get_symbols();
  std::vector<std::string> string_to_vector(std::string string);
  void symbols_to_tree(std::vector<std::string> symbols);
  void read_machine_data();
  void build_state_trees();
  SymbolNode get_current_symbol_node(SymbolNode const &root);

public:
  bool new_state();
  std::vector<Tape> tapes;
  TuringMachine(std::string filename);
  void start();
};