#include "symbol_node.hpp"
#include <string>
SymbolNode::SymbolNode(std::string value) : value(value) {}

bool SymbolNode::operator<(const SymbolNode &node) const { return value < node.value; }