#include "bin/arg_parser.hpp"
#include <iostream>
#include <stdexcept>
int main(int argc, char *argv[]) {
  try {
    ArgParser::parse_args(argc, argv);
  } catch (std::runtime_error& e) {
    std::cout<<e.what();
  }
}