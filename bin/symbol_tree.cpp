#include "symbol_tree.hpp"
#include "deque"
#include "symbol_node.hpp"
#include <map>
#include <string>

SymbolTree::SymbolTree(std::string value) : root(SymbolNode(value)) {}

void SymbolTree::insert_branch(std::deque<std::string> nodes) {
  SymbolNode *node = &root;
  while (!nodes.empty()) {
    node->adjacent_nodes.insert(std::pair<std::string, SymbolNode>(
        nodes.front(), SymbolNode(nodes.front())));
    node = &node->adjacent_nodes.at(nodes.front());
    nodes.pop_front();
  }
}