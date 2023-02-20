#include "arg_parser.hpp"
#include "turing_machine.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>
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

void ArgParser::parse_args(int argc, char *argv[]) {
  std::vector<std::string> arg_list(argv, argv + argc);
  if (argc < 2) {
    throw std::runtime_error(
        "UTM: error: Missing arguments, use -h for more information \n");
  }
  if (arg_list[1] == "-h") {
    help();
  }
  if (arg_list[1] == "-f") {
    if (argc < 3) {
      throw std::runtime_error("UTM: error: filename expected \n");
    }
    std::vector<std::string> filenames;
    for (int i = 2; i < argc; i++) {
      filenames.push_back(arg_list[i]);
    }
    start_machine(filenames);
  }
}

void ArgParser::start_machine(std::vector<std::string> filenames) {
  std::vector<TuringMachine> machines;
  for (int i = 0; i < filenames.size(); i++) {
    machines.push_back(TuringMachine(filenames[i]));
    machines[i].start();
  }
  bool finished = 1;
  while (finished) {
    finished = 0;
    system("clear");
    for (int i = 0; i < machines.size(); i++) {
      finished += machines[i].new_state();
      machines[i].tapes.front().print_state();
    }
  }
}