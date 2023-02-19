#include "string"
#include "vector"
#include <string>
#include <vector>

class ArgParser {
  static void help();
  static void start_machine(std::string filename);
  static std::vector<char> options;
  static std::vector<std::string> definitions;

public:
  static void parse_args(int argc, char *argv[]);
};