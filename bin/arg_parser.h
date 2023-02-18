#include "string"
#include "vector"
#include <string>
#include <vector>

class ArgParser {
  static void start_machine(std::string filename);
  static void help();
  static void validate_arguments();

public:
  static void parse_args(int argc, char *argv[]);
  static std::vector<char> options;
  static std::vector<std::string> definitions;
};