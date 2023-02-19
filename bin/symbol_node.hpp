#pragma once
#include <map>
#include <string>

class SymbolNode {
public:
  SymbolNode(std::string value);
  std::string value;
  std::map<std::string, SymbolNode> adjacent_nodes;
};