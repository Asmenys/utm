#include "vector"
#include <string>
#include <vector>
#include "string"

class ArgInterpretor {
  static void interpret_args(int argc, char *argv[]);
  static std::vector<char> options;
  static std::vector<std::string> definitions;

private:
  static void start_machine();
  static void help();
};