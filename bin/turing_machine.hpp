#include "symbol_tree.hpp"
#include "tape.hpp"
#include <fstream>
#include <map>
#include <string>

class TuringMachine {

  std::string current_state;
  std::map<std::string, SymbolTree> tree_map;
  std::ifstream tape_file;
  bool tape_exists(std::string filename);
  void open_file(std::string filename);

public:
  TuringMachine(std::string filename);
  std::string state;
};