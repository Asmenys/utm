#pragma once
#include <map>
#include <string>
#include "map"
class SymbolNode {
public:
  SymbolNode(std::string value);
  std::string value;
  std::map<std::string, SymbolNode> adjacent_nodes;
  
  bool operator<(const SymbolNode &node) const;
};