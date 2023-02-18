#include "arg_interpretor.h"
#include "iomanip"
#include "iostream"
#include <string>
#include <vector>

std::vector<char> ArgInterpretor::options = {'h', 'f'};
std::vector<std::string> ArgInterpretor::definitions = {
    "shows this message", "<filename> - Read instructions from filename"};

void ArgInterpretor::help() {
  std::cout << "USAGE: ./utm.sh [options] <inputs> \n\n";
  std::cout << "OPTIONS:\n";
  for (int i = 0; i < options.size(); i++) {
    std::cout << std::setw(2) << options.at(i) << std::setw(10)
              << definitions.at(i) << std::endl;
  }
}