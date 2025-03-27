// Copyright 2024 Chris Lambert
#include <iostream>
#include <string>
#include "RandWriter.hpp"

using std::stoi;

int main(int argc, char* argv[]) {
  string text;

  string line;

  while (getline(std::cin, line)) {
    text += line;
  }

  int order = stoi(argv[1]);
  int length = stoi(argv[2]);

  RandWriter rw(text, order);

  std::string initial_kgram = text.substr(0, order);
  std::string genText = rw.generate(initial_kgram, length);

  std::cout << genText << std::endl;

  // std::cout << rw << std::endl;

  return 0;
}
