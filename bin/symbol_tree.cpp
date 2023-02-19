#include "symbol_tree.hpp"
#include "symbol_node.hpp"
#include <set>
#include <string>

SymbolTree::SymbolTree(std::string value) : root(SymbolNode(value)) {}

void SymbolTree::insert_branch(std::deque<std::string> nodes) {
  SymbolNode node = root;
  while (!nodes.empty()) {
    node = *node.adjacent_nodes.insert(SymbolNode(nodes.front())).first;
    nodes.pop_front();
  }
}