#include "arg_parser.h"
#include "iomanip"
#include "iostream"
#include "stdexcept"
#include <string>
#include <vector>

std::vector<char> ArgParser::options = {'h', 'f'};
std::vector<std::string> ArgParser::definitions = {
    "shows this message", "<filename> - Read instructions from filename"};

void ArgParser::help() {
  std::cout << "USAGE: ./utm.sh [options] <inputs> \n\n";
  std::cout << "OPTIONS:\n";
  for (int i = 0; i < options.size(); i++) {
    std::cout << std::setfill(' ') << '-' << options.at(i) << std::setw(2)
              << ' ' << std::setw(10) << ' ' << definitions.at(i) << std::endl;
  }
}

void ArgParser::start_machine(char filename[]) {}

void ArgParser::parse_args(int argc, char *argv[]) {
  if (argc < 2) {
    throw std::runtime_error("UTM: error: no input files \n");
  }
  if (argc > 3) {
    throw std::runtime_error("UTM: error: too many arguments \n");
  }
  for (int i = 1; i < argc; i++) {
    if (argv[i][1] == 'h') {
      help();
    }
    if (argv[i][1] == 'f') {
      start_machine(argv[i+1]);
    }
  }
}