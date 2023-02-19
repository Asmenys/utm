#pragma once
#include <set>
#include <string>
class SymbolNode {
public:
  SymbolNode(std::string value);
  std::string value;
  std::set<SymbolNode> adjacent_nodes;
  bool operator<(const SymbolNode &node) const;
};