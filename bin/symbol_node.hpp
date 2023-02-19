#include <string>
#include <unordered_set>
class SymbolNode {
public:
  std::string value;
  std::unordered_set<SymbolNode> adjacent_nodes;
};