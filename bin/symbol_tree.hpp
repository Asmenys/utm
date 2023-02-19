#include "deque"
#include "symbol_node.hpp"
#include <deque>
#include <string>
class SymbolTree {
public:
  SymbolTree(std::string value);
  SymbolNode root;
  void insert_branch(std::deque<std::string> nodes);
};